#include "Quiet_pch.h"

#include "Quiet/Renderer/GraphicsContext.h"
#include "Quiet/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Quiet {
	
	Scope<GraphicsContext>GraphicsContext::Create(void* window) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:		QUIET_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:		return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
			case RendererAPI::API::Vulkan:		QUIET_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!"); return nullptr;
			case RendererAPI::API::Direct3D:	QUIET_CORE_ASSERT(false, "RendererAPI::Direct3D is currently not supported!"); return nullptr;
		}

		QUIET_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}