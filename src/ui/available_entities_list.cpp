
#include "../app/prelude.h"
#include "available_entities_list.h"
#include "../prelude.h"


#include "../prelude.h"


#include "imgui/imgui.h"
#include "../utils/class_factory.h"
#include "../utils/crypto.h"

#include "uiapp.h"
#include "../app/prelude.h"


namespace simstudio {

	void AvailableEntitiesList::Draw()
	{


		if (ImGui::TreeNode("Process modeling")) {
			_AddAndDrawEntityIfValid("Source", "source");
			_AddAndDrawEntityIfValid("Buffer", "buffer");
			_AddAndDrawEntityIfValid("Station", "station");
			_AddAndDrawEntityIfValid("Drain", "drain");
			_AddAndDrawEntityIfValid("Loader", "loader");
			_AddAndDrawEntityIfValid("Split", "split");
			_AddAndDrawEntityIfValid("Merge", "merge");
			_AddAndDrawEntityIfValid("Router", "router");

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Transport")) {
			_AddAndDrawEntityIfValid("Conveyor", "conveyor");
			_AddAndDrawEntityIfValid("Single lane", "singlelane");
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Logistics")) {
			_AddAndDrawEntityIfValid("Warehouse", "warehosue");
			//_AddAndDrawEntityIfValid("Andon system", "ad");
			//_AddAndDrawEntityIfValid("Canban sytem", "warehosue");
			//_AddAndDrawEntityIfValid("Canban", "warehosue");
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Energy")) {
			_AddAndDrawEntityIfValid("Solar collectors", "solarcollector");
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Data")) {
			_AddAndDrawEntityIfValid("Function", "function");
			_AddAndDrawEntityIfValid("List", "list");
			_AddAndDrawEntityIfValid("Table", "table");
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Vehicles")) {
			_AddAndDrawEntityIfValid("Agv", "agv");
			ImGui::TreePop();

		}
	}

	void AvailableEntitiesList::_AddAndDrawEntityIfValid(const String& lang, const String& type)
	{
		if (ImGui::Button(lang.c_str())) {
			_AddEntityOfType(type);
		}
	}

	void AvailableEntitiesList::_AddEntityOfType(const String& type)
	{
		if (_app) {
			const auto entity = ClassFactory::Instance()->Construct<Entity>(type);
			if (entity) {
				entity->_name = F("{}_{}", type, 0);
				entity->_uid = Crypto::Uuid_V4();

				_app->_world->AddEntity(entity);

				LogI << "Successfully added entity";
			}
		}
	}
}









