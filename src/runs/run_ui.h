#pragma once
#include "../prelude.h"


#if IS_WINDOWS_PLATFORM

namespace simstudio {


	class App;

	void run_ui(App& app);
	void _draw(App& app);
}

#endif