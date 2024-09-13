#include "imgui/imgui.h"

#include "_dispatchers.h"

#include "../../app/prelude.h"

#include "SimCore/Prelude.h"







namespace simstudio {
	void DrawBuffer(Shared<World>& world, Shared<Buffer>& entity) {

		ImGui::InputScalar("limit", ImGuiDataType_S64, &entity->_limit);
		ImGui::InputScalar("criticalLimit", ImGuiDataType_S64, &entity->_criticalLimit);


	}
}