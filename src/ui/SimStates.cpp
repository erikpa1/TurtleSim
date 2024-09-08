
#include "SimCore/AnyEventEmmiter.h"
#include "SimCore/Prelude.h"
#include "SimStates.h"

#include "imgui/imgui.h"
#include "uiapp.h"

#include "../app/prelude.h"


namespace simstudio {

	void SimStates::SetApp(UiApp* app)
	{
		_app = app;

		AnyEventEmitter::I().RegisterEvent("SimulationStarted", this->shared_from_this(), &SimStates::Prepare);

	}

	void SimStates::Draw()
	{

		_DrawStations();
		_DrawConveyors();
		_DrawBuffers();


		return;


		enum ContentsType { CT_Text, CT_FillButton };
		static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
		static bool display_headers = true;
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
				for (int column = 0; column < 3; column++)
				{
					ImGui::TableSetColumnIndex(column);
					char buf[32];
					sprintf(buf, "Hello %d,%d", column, row);
					if (contents_type == CT_Text) {
						ImGui::TextUnformatted(buf);
					}

					else if (contents_type == CT_FillButton) {
						ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f));
					}

				}

				row += 1;
			}
			ImGui::EndTable();
		}

	}

	void SimStates::Update()
	{

	}

	void SimStates::Prepare()
	{

		const auto& entites = _app->_world->_entities;
		for (const auto& iter : entites) {
			const auto& entity = iter.second;

			const auto entity_type = entity->Type();

			if (entity_type == Buffer::ClassType()) {
				_buffersPlot.push_back(0);
			}
			else if (entity_type == Conveyor::ClassType()) {
				_conveyorsPlot.push_back(0);
			}

		}

	}

	void SimStates::_DrawBuffers()
	{
		if (_buffersPlot.size() > 0) {
			const auto& entites = _app->_world->_entities;

			int index = 0;

			for (const auto& iter : entites) {

				const auto entity_type = iter.second->Type();

				if (entity_type == Buffer::ClassType()) {
					auto buffer = StaticCast<Buffer>(iter.second);
					_buffersPlot[index] = buffer->_buffer.size();

					index += 0;
				}
			}

			const auto& arr = _buffersPlot.data();

			ImGui::PlotLines("Buffers occupancy:", arr, IM_ARRAYSIZE(arr));
			ImGui::PlotHistogram("Histogram", arr, IM_ARRAYSIZE(arr), 0, NULL, 0.0f, 1.0f, ImVec2(0, 80.0f));

		}

	}

	void SimStates::_DrawConveyors()
	{

		if (_conveyorsPlot.size() > 0) {

			const auto& entites = _app->_world->_entities;

			int index = 0;

			for (const auto& iter : entites) {

				const auto entity_type = iter.second->Type();

				if (entity_type == Conveyor::ClassType()) {
					auto conveyor = StaticCast<Conveyor>(iter.second);
					_conveyorsPlot[index] = conveyor->_buffer.size();

					index += 0;
				}
			}


			const auto& arr = _conveyorsPlot.data();

			ImGui::PlotLines("Conveyors occupancy:", arr, IM_ARRAYSIZE(arr));
			ImGui::PlotHistogram("Histogram", arr, IM_ARRAYSIZE(arr), 0, NULL, 0.0f, 1.0f, ImVec2(0, 80.0f));


		}

	}

	void SimStates::_DrawStations()
	{
		const auto& entites = _app->_world->_entities;
		for (const auto& iter : entites) {
			const auto& entity = iter.second;

			static int val = entity->GetStateInt();

			LogI << entity->_name << " " << entity->GetStateInt();

			ImGui::InputInt(entity->_name.c_str(), &val);
		}


	}
}