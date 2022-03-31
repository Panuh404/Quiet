#include "Quiet_pch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Quiet {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			QUIET_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);

		case RendererAPI::Vulkan:
			QUIET_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!");
			return nullptr;

		case RendererAPI::Direct3D:
			QUIET_CORE_ASSERT(false, "RendererAPI::Direct3D is currently not supported!");
			return nullptr;
		}
		QUIET_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			QUIET_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, size);

		case RendererAPI::Vulkan:
			QUIET_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!");
			return nullptr;

		case RendererAPI::Direct3D:
			QUIET_CORE_ASSERT(false, "RendererAPI::Direct3D is currently not supported!");
			return nullptr;
		}
		QUIET_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}