#include "Quiet_pch.h"

#include "Quiet/Renderer/RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Quiet {	
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;	

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::None:		QUIET_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:		return CreateScope<OpenGLRendererAPI>();
		case RendererAPI::API::Vulkan:		QUIET_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!"); return nullptr;
		case RendererAPI::API::Direct3D:	QUIET_CORE_ASSERT(false, "RendererAPI::Direct3D is currently not supported!"); return nullptr;
		}

		QUIET_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}