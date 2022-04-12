#include "Quiet_pch.h"
#include "Quiet/Core/Input.h"

#ifdef QUIET_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsInput.h"
#endif

namespace Quiet
{
	Scope<Input> Input::s_Instance = Input::Create();
	Scope<Input> Input::Create()
	{
		#ifdef QUIET_PLATFORM_WINDOWS
			return CreateScope<WindowsInput>();
		#else
			QUIET_CORE_ASSERT(false, "Unknown Platform!");
			return nullptr;
		#endif
	}
	
}