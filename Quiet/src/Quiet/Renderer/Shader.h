#pragma once
#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

namespace Quiet {

	class Shader {
	private:
		uint32_t m_RendererID;

	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& name, const int& value) = 0;
		virtual void SetFloat(const std::string& name, const float& values) = 0;
		virtual void SetFloat2(const std::string& name, const glm::vec2& values) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& values) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& values) = 0;
		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader>Create(const std::string& filepath);
		static Ref<Shader>Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
	};

	class ShaderLibrary {
	public:
		void Add(const Ref<Shader>& shader);
		void Add(const std::string& name, const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);
		
		Ref<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}