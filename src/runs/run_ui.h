#pragma once
#include "../prelude.h"


#if IS_WINDOWS_PLATFORM

namespace simstudio {


	class World;

	void run_ui(World& app);
	void _draw(World& app);
}

#endif