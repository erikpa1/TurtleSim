

#include "SimStates.h"

#include "imgui/imgui.h"
#include "uiapp.h"

#include "../app/prelude.h"

namespace simstudio {

	void SimStates::SetApp(UiApp* app)
	{
		_app = app;
	}

	void SimStates::Draw()
	{
		static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
		ImGui::PlotLines("Frame Times", arr, IM_ARRAYSIZE(arr));
		ImGui::PlotHistogram("Histogram", arr, IM_ARRAYSIZE(arr), 0, NULL, 0.0f, 1.0f, ImVec2(0, 80.0f));


		enum ContentsType { CT_Text, CT_FillButton };
		static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
		static bool display_headers = false;
		static int contents_type = CT_Text;

		if (ImGui::BeginTable("table1", 3, flags))
		{
			// Display headers so we can inspect their interaction with borders
			// (Headers are not the main purpose of this section of the demo, so we are not elaborating on them now. See other sections for details)

			const auto& entites = _app->_world->_entities;

			if (display_headers)
			{
				for (const auto& iter : entites) {
					ImGui::TableSetupColumn(iter.second->_name.c_str());
				}
				ImGui::TableHeadersRow();
			}



			int row = 0;
			for (const auto& iter : entites)
			{
				const auto& entity = iter.second;

				ImGui::TableNextRow();
				for (int column = 0; column < 1; column++)
				{
					ImGui::TableSetColumnIndex(column);
					char buf[32];
					sprintf(buf, "Hello %d,%d", column, row);
					if (contents_type == CT_Text)
						ImGui::TextUnformatted(buf);
					else if (contents_type == CT_FillButton)
						ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f));
				}

				row += 1;
			}
			ImGui::EndTable();
		}

	}
	void SimStates::Update()
	{

	}
}