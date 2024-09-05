#pragma once

#include "SimCore/Prelude.h"

namespace simstudio {

	class UiApp;

	class SimStates {

	public:
		void SetApp(UiApp* app);
		void Draw();
		void Update();

	private:
		UiApp* _app;

	};

}