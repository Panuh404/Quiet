#include "Quiet_pch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Quiet {
	
	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:    QUIET_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return new OpenGLVertexArray();
		}
		QUIET_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}

