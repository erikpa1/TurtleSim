#include "entity_properties.h"

#include "../app/prelude.h"

#include "uiapp.h"


#include "../../external/imgui/imgui.h"



namespace simstudio {


	void EntityPropertiesView::Draw()
	{
		if (_app) {

			auto& entity = _app->_activeEntity;

			if (entity) {

				static char str0[128] = "Hello, world!";
				ImGui::InputText("Name:", str0, IM_ARRAYSIZE(str0));

				ImGui::Text("Some properties");

				ImGui::Text(entity->_name.c_str());
				ImGui::Text(entity->_uid.c_str());

			}
			else {
				ImGui::Text("No active entity");
			}
		}
		else {
			ImGui::Text("App is invalid");
		}


	}

}