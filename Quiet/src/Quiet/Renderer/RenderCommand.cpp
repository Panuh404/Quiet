#include "Quiet_pch.h"

#include "Quiet/Renderer/RenderCommand.h"

namespace Quiet {
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}