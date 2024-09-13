#pragma once

#include "SimCore/Prelude.h"

namespace simstudio {

	class UiApp;

	class SimStates : public EnableShare<SimStates> {

	public:
		void SetApp(UiApp* app);
		void Draw();
		void Update();
		void Prepare();

	private:
		UiApp* _app;

		void _DrawProgress();
		void _DrawBuffers();
		void _DrawConveyors();
		void _DrawStations();

	public:
		Array<float> _buffersPlot;
		Array<float> _conveyorsPlot;

		String _progressText = "Here";

	};

}