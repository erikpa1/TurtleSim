#include "entity_properties.h"

#include "../app/prelude.h"

#include "uiapp.h"


#include "imgui/imgui.h"

#include "imgui/immygui.h"



namespace simstudio {



	float floatValue = 0.0f;
	int intValue = 0;
	long longValue = 0L;

	void EntityPropertiesView::Draw()
	{
		if (_app) {

			auto& entity = _app->_activeEntity;

			if (entity) {

				static char str0[128] = "Hello, world!";
				ImGui::CstrInput("Label 1:", str0, IM_ARRAYSIZE(str0));
				ImGui::Text("Some properties");

				ImGui::Text(entity->_name.c_str());
				ImGui::Text(entity->_uid.c_str());


				ImGui::StringInput("String Value:", entity->_name);
				ImGui::FloatInput("Float Value:", &floatValue);
				ImGui::IntInput("Int Value:", &intValue);
				ImGui::LongInput("Long Value:", &longValue);


				_dispatcher.Draw();


			}
			else {
				ImGui::Text("No active entity");
			}
		}
		else {
			ImGui::Text("App is invalid");
		}


	}

	void EntityPropertiesView::SetApp(UiApp* app)
	{
		_app = app;
		_dispatcher._app = app;
	}

}