#pragma once

//-----------------------------------------------------------------------------
// QUIET PRECOMPILED HEADERS
//-----------------------------------------------------------------------------
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

#include "Quiet/Core/Log.h"
#include "Quiet/Debug/Instrumentor.h"

#ifdef QUIET_PLATFORM_WINDOWS
	#include <Windows.h>
#endif