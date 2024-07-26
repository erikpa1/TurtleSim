#include "../app/prelude.h"
#include "available_entities_list.h"


#if IS_WINDOWS_PLATFORM
#include "../../external/imgui/imgui.h"


namespace simstudio {

	void AvailableEntitiesList::Draw()
	{
		if (ImGui::TreeNode("Process modeling")) {
			ImGui::Button("Source");
			ImGui::Button("Station");
			ImGui::Button("Buffer");
			ImGui::Button("Drain");
			ImGui::Button("Loader");
			ImGui::Button("Split");
			ImGui::Button("Merge");
			ImGui::Button("Router");
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Transport")) {
			ImGui::Button("Conveyor");
			ImGui::Button("Single lane");
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Logistics")) {
			ImGui::Button("Warehouse");
			ImGui::Button("Andon system");
			ImGui::Button("Canban sytem");
			ImGui::Button("Canban");
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Energy")) {
			ImGui::Button("Solar collectors");
			ImGui::Button("Wind Turbine");
			ImGui::Button("Electricity grid");
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Data")) {
			ImGui::Button("Python Script");
			ImGui::Button("List");
			ImGui::Button("Table");
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Vehicles")) {
			ImGui::Button("Agv");
			ImGui::TreePop();

		}




	}
}









#endif