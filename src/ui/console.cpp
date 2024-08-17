

#include "console.h"

#include "imgui/imgui.h"

namespace simstudio {
	void Console::Draw()
	{
		bool isOpen = true;

		ImGui::ShowDebugLogWindow(&isOpen);
	}
}