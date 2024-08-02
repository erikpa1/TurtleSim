#pragma once

#include "../prelude.h"

namespace simstudio {

	class UiApp;

	class AppControls {

	public:

		void Draw();


		UiApp* _app;


	private:

		void _StartNewProject();
		void _OpenProject();


	};

}