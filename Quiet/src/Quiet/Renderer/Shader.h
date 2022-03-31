#pragma once

#include <string>

namespace Quiet {

	class Shader {
	private:
		uint32_t m_RendererID;

	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		~Shader();

		void Bind() const;
		void Unbind() const;
	};
}