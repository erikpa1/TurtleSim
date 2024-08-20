#include "run_ui.h"

#if IS_WINDOWS_PLATFORM

#include "../prelude.h"



#include "../app/prelude.h"

#include "../../external/imgui/imgui.h"

#include "../utils/exe_dir.h"



using namespace ImGui;

namespace simstudio {
	void run_ui(World& app)
	{

		_draw(app);

	}


	void _draw_entites(HashMap<Shared<Entity>>& _entities) {


		for (const auto& iter : _entities)
		{
			auto& entity = iter.second;
			ImGui::Button(entity->_name.c_str());


			ImGui::LabelText("Operation time: 10:00", "");


		}


	}

	void _draw(World& app)
	{
		static float f = 0.0f;
		static int counter = 0;

		static bool my_tool_active = false;

		ImGui::NewFrame();


		ImGui::Begin("Controls", &my_tool_active, ImGuiWindowFlags_MenuBar);


		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open..", "Ctrl+O")) {
					String example_file = F("{}\\{}", GetSolutionDirectory(), "example.xml");
					app.LoadFromXmlFile(example_file);
				}
				if (ImGui::MenuItem("Save", "Ctrl+S")) {
					LogE << "Going to save xml";
				}
				if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; }
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}


		ImGui::SameLine();





		_draw_entites(app._entities);


		ImGui::End();

		// Rendering
		ImGui::Render();
		ImGui::UpdatePlatformWindows();
	}

}

#endif