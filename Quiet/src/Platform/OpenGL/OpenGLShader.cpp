#include "Quiet_pch.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Quiet
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "VERTEX")						{ return GL_VERTEX_SHADER;   }
		if (type == "FRAGMENT" || type == "PIXEL")	{ return GL_FRAGMENT_SHADER; }
		if (type == "GEOMETRY")						{ return GL_GEOMETRY_SHADER; }
		if (type == "COMPUTE")						{ return GL_COMPUTE_SHADER;  }
		QUIET_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}
	
	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		QUIET_PROFILE_FUNCTION();
		std::string ShaderSource = ReadFile(filepath);
		auto sources = PreProcess(ShaderSource);
		CompileShaders(sources);

		// Find Shader Name
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}
	
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource) :
		m_Name(name) 
	{
		QUIET_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSource;
		sources[GL_FRAGMENT_SHADER] = fragmentSource;
		CompileShaders(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		QUIET_PROFILE_FUNCTION();
		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		QUIET_PROFILE_FUNCTION();		
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
				in.close();
			}
			else
			{
				QUIET_CORE_ERROR("Could not read from file '{0}'", filepath);
			}
		}
		else
		{
			QUIET_CORE_ERROR("Failed to open file: {0}", filepath);
		}
		return result;
	}
	
	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string source)
	{
		QUIET_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> shaderSources;
		const char* typeToken = "#TYPE:";
		size_t typeTokenLength = strlen(typeToken);
		
		//  Start of the shader type declaration line
		size_t pos = source.find(typeToken, 0); 
		
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos); // End of shader type declaration line
			QUIET_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1; // Start shader type name (after #TYPE: keyword)
			std::string type = source.substr(begin, eol - begin);

			size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
			pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}
		return shaderSources;
	}

	void OpenGLShader::CompileShaders(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		QUIET_PROFILE_FUNCTION();
		GLuint program = glCreateProgram();
		QUIET_CORE_ASSERT(shaderSources.size() <= 4, "Too many shaders!");
		std::array<GLenum, 4> glShaderIDs;
		int glShaderIDindex = 0;
		
		for (auto& key : shaderSources)
		{
			GLenum type = key.first;
			const std::string& source = key.second;

			GLuint shader = glCreateShader(type);
			const GLchar* shaderSrc = source.c_str();
			glShaderSource(shader, 1, &shaderSrc, 0);
			glCompileShader(shader);
			
			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
				glDeleteShader(shader);

				QUIET_CORE_ERROR("{0}", infoLog.data());
				QUIET_CORE_ASSERT(false, "Shader Compilation failure!");
				return;
			}
			glAttachShader(program, shader);
			glShaderIDs[glShaderIDindex++] = (shader);
		}
		
		glLinkProgram(program);
		
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
			
			std::vector<GLchar> infoLog(maxLength);			
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			glDeleteProgram(program);
			
			for (auto& id : glShaderIDs)
			{
				glDeleteShader(id);
			}
			QUIET_CORE_ERROR("{0}", infoLog.data());
			QUIET_CORE_ASSERT(false, "Shader link failure!");
			return;
		}
		for (auto& id : glShaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}
		m_RendererID = program;
	}

	void OpenGLShader::Bind() const
	{
		QUIET_PROFILE_FUNCTION();
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		QUIET_PROFILE_FUNCTION();
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)						{ QUIET_PROFILE_FUNCTION(); UploadUniformInt(name, value);				}
	void OpenGLShader::SetIntArr(const std::string& name, int* values, uint32_t count)	{ QUIET_PROFILE_FUNCTION(); UploadUniformIntArr(name, values, count);	}
	void OpenGLShader::SetFloat(const std::string& name, float values)					{ QUIET_PROFILE_FUNCTION(); UploadUniformFloat(name, values);			}
	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& values)		{ QUIET_PROFILE_FUNCTION(); UploadUniformFloat2(name, values);			}
	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& values)		{ QUIET_PROFILE_FUNCTION(); UploadUniformFloat3(name, values);			}
	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& values)		{ QUIET_PROFILE_FUNCTION(); UploadUniformFloat4(name, values);			}
	void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& matrix)		{ QUIET_PROFILE_FUNCTION(); UploadUniformMat3(name, matrix);			}
	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& matrix)		{ QUIET_PROFILE_FUNCTION(); UploadUniformMat4(name, matrix);			}

	
	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformIntArr(const std::string& name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, values.r, values.g);
	}
	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, values.r, values.g, values.b);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, values.r, values.g, values.b, values.a);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}