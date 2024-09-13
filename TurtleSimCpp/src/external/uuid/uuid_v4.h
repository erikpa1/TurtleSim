#pragma once

#if IS_WINDOWS_PLATFORM
#include "endianness.h"
#include "uuid_v4_windows.h"
#else
#include "uuid_v4_wasm.h"
#endif