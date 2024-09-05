#pragma once

#include "SimCore/Prelude.h"

namespace simstudio {

	class UiApp;

	class SimulationControls {

	public:
		void SetApp(UiApp* app);
		void Draw();
		void Update();

		bool _isSimulating = false;

	private:

		UiApp* _app;

		void _StartSimulation();
		void _PauseSimulation();
		void _RefreshSimulation();




	};



}