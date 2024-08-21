#pragma once

#include "../prelude.h"
#include "./entity_properties/DrawPropertiesDispatcher.h"

namespace simstudio {


	class UiApp;


	class EntityPropertiesView {

	public:

		void Draw();
		void SetApp(UiApp* app);

	public:

		UiApp* _app = nullptr;

	private:

		DrawPropertiesDispatcher _dispatcher;

	};


}