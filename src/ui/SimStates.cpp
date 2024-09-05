

#include "SimStates.h"

#include "imgui/imgui.h"
#include "uiapp.h"

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
			if (display_headers)
			{
				ImGui::TableSetupColumn("One");
				ImGui::TableSetupColumn("Two");
				ImGui::TableSetupColumn("Three");
				ImGui::TableHeadersRow();
			}

			for (int row = 0; row < 5; row++)
			{
				ImGui::TableNextRow();
				for (int column = 0; column < 3; column++)
				{
					ImGui::TableSetColumnIndex(column);
					char buf[32];
					sprintf(buf, "Hello %d,%d", column, row);
					if (contents_type == CT_Text)
						ImGui::TextUnformatted(buf);
					else if (contents_type == CT_FillButton)
						ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f));
				}
			}
			ImGui::EndTable();
		}

	}
	void SimStates::Update()
	{

	}
}