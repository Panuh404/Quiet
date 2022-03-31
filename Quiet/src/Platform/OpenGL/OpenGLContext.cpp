#include "Quiet_pch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Quiet {
	
	OpenGLContext::OpenGLContext(GLFWwindow* windowsHandle) :
		m_WindowHandle(windowsHandle)
	{
		QUIET_CORE_ASSERT(windowsHandle, "Window handle is null!");
		
	}
	
	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		QUIET_CORE_ASSERT(status, "Failed to initialize Glad");

		QUIET_CORE_INFO("OpenGL Info:");
		QUIET_CORE_INFO(" -Vendor:	{0}", glGetString(GL_VENDOR));
		QUIET_CORE_INFO(" -Renderer:	{0}", glGetString(GL_RENDERER));
		QUIET_CORE_INFO(" -Version:	{0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}
}