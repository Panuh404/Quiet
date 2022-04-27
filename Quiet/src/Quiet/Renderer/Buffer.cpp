#include "Quiet_pch.h"

#include "Quiet/Renderer/Buffer.h"
#include "Quiet/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Quiet
{
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		QUIET_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLVertexBuffer>(size);
			case RendererAPI::API::Vulkan:		QUIET_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!"); return nullptr;
			case RendererAPI::API::Direct3D:	QUIET_CORE_ASSERT(false, "RendererAPI::Direct3D is currently not supported!"); return nullptr;
		}
		QUIET_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		QUIET_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLVertexBuffer>(vertices, size);
			case RendererAPI::API::Vulkan:		QUIET_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!"); return nullptr;
			case RendererAPI::API::Direct3D:	QUIET_CORE_ASSERT(false, "RendererAPI::Direct3D is currently not supported!"); return nullptr;
		}
		QUIET_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		QUIET_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLIndexBuffer>(indices, count);
			case RendererAPI::API::Vulkan:		QUIET_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!"); return nullptr;
			case RendererAPI::API::Direct3D:	QUIET_CORE_ASSERT(false, "RendererAPI::Direct3D is currently not supported!"); return nullptr;
		}
		QUIET_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}