#pragma once

namespace Quiet {

	enum class RendererAPI {
		None = 0,
		OpenGL = 1,
		Vulkan = 2,
		Direct3D = 3
	};

	class Renderer {
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};
}

