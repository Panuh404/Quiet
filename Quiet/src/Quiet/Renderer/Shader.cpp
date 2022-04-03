#include "Quiet_pch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Quiet {

	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:		QUIET_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLShader(vertexSource, fragmentSource);
		case RendererAPI::API::Vulkan:		QUIET_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!"); return nullptr;
		case RendererAPI::API::Direct3D:	QUIET_CORE_ASSERT(false, "RendererAPI::Direct3D is currently not supported!"); return nullptr;
		}
		QUIET_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}