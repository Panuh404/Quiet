#pragma once
#include "Quiet/Renderer/Shader.h"

#include <glm/glm.hpp>

// TEMP
typedef unsigned int GLenum;

namespace Quiet
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArr(const std::string& name, int* values, uint32_t count) override;
		virtual void SetFloat(const std::string& name, float values) override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& values) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& values) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& values) override;
		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override;
		
		virtual const std::string& GetName() const override { return m_Name; }

		// Uniforms Handle
		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformIntArr(const std::string& name, int* values, uint32_t count);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values);		
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		uint32_t m_RendererID;
		std::string m_Name;

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string source);
		void CompileShaders(const std::unordered_map<GLenum, std::string>& shaderSources);
	};
}