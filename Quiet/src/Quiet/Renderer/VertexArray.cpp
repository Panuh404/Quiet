#include "Quiet_pch.h"

#include "Quiet/Renderer/VertexArray.h"
#include "Quiet/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Quiet
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		QUIET_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLVertexArray>();
			case RendererAPI::API::Vulkan:		QUIET_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!"); return nullptr;
			case RendererAPI::API::Direct3D:	QUIET_CORE_ASSERT(false, "RendererAPI::Direct3D is currently not supported!"); return nullptr;
		}
		QUIET_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}