#include "Quiet_pch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Quiet {
	
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
	
}