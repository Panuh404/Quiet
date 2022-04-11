#pragma once

//-----------------------------------------------------------------------------
// [SECTION] QUIET PRECOMPILED HEADERS
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

// Logger
#include "Quiet/Core/Log.h"

#ifdef QUIET_PLATFORM_WINDOWS
	#include <Windows.h>
#endif