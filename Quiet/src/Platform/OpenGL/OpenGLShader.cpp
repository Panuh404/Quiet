#include "Quiet_pch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Quiet {

	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource) {

		// Create an empty vertex and fragment shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the vertex and fragment shader source code to GL
		const GLchar* vertexSrc = (const GLchar*)vertexSource.c_str();
		glShaderSource(vertexShader, 1, &vertexSrc, 0);
		const GLchar* fragmentSrc = (const GLchar*)fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &fragmentSrc, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
			
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);

			QUIET_CORE_ERROR("{0}", infoLog.data());
			QUIET_CORE_ASSERT(false, "Vertex Shader Compilation failure!");
			return;
		}
		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
			
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			QUIET_CORE_ERROR("{0}", infoLog.data());
			QUIET_CORE_ASSERT(false, "Fragment Shader Compilation failure!");
			return;
		}

		// Now link them together into a program.
		m_RendererID = glCreateProgram();
		// Attach our shaders to our program
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);
		// Link our program
		glLinkProgram(m_RendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);
			
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_RendererID);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			QUIET_CORE_ERROR("{0}", infoLog.data());
			QUIET_CORE_ASSERT(false, "Shader link failure!");
			return;
		}
		// Always detach shaders after a successful link.
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const {
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}
	void OpenGLShader::UploadUniformInt(const std::string& name, int value)	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}
	void OpenGLShader::UploadUniformFloat(const std::string& name, const float& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}
	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, values.r, values.g);
	}
	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, values.r, values.g, values.b);
	}
	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, values.r, values.g, values.b, values.a);
	}
	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}