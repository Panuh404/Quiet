#include "Quiet_pch.h"
#include "Quiet/Core/Window.h"

#ifdef QUIET_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Quiet
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef QUIET_PLATFORM_WINDOWS
			return CreateScope<WindowsWindow>(props);
		#else
			QT_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}
}