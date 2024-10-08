#include "entities_hierarchy.h"


#include "../app/prelude.h"



#include "imgui/imgui.h"
#include "uiapp.h"



namespace simstudio {

	void EntitiesHierarchy::Draw()
	{
		if (_app) {

			for (const auto& pair : _app->_world->_entities) {
				auto& entity = pair.second;

				if (ImGui::Button(entity->_name.c_str())) {
					_app->_activeEntity = entity;
				}
			}
		}
		else {
			ImGui::Text("Application is invalid");
		}


	}
}






