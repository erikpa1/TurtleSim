

#include "SimControls.h"

#include "imgui/imgui.h"

#include "uiapp.h"

#include "../app/world.h"

namespace simstudio {

	void SimulationControls::SetApp(UiApp* app)
	{
		_app = app;
	}
	void SimulationControls::Draw()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Simulation"))
			{
				if (ImGui::MenuItem("Run")) {
					_StartSimulation();
				}
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}

	void SimulationControls::Update()
	{
		if (_isSimulating) {
			_app->_world->Step();
		}

	}

	void SimulationControls::_StartSimulation()
	{
		_isSimulating = true;
	}

	void SimulationControls::_PauseSimulation()
	{
		_isSimulating = true;
	}

	void SimulationControls::_RefreshSimulation()
	{

	}
}