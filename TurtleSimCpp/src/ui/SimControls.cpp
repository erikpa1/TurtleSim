

#include "SimCore/AnyEventEmmiter.h"

#include "SimControls.h"

#include "imgui/imgui.h"

#include "uiapp.h"

#include "../app/world.h"
#include "../app/stepper.h"
#include "../statistics/app_report_collector.h"

namespace simstudio {

	void SimulationControls::SetApp(UiApp* app)
	{
		_app = app;
	}
	void SimulationControls::Draw()
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Simulation"))
			{
				if (ImGui::MenuItem("Run")) {
					_StartSimulation();
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
	}

	void SimulationControls::Update()
	{

		if (_isSimulating) {
			const auto& world = _app->_world;
			const auto stepper = world->_stepper;


			if (stepper._stepIndex <= stepper._endIndex) {
				world->Step();
			}
			else {
				LogI << "Simulation ended";

				SaveStatisticsRecord(*world);

				_isSimulating = false;
			}

		}

	}

	void SimulationControls::_StartSimulation()
	{
		_isSimulating = true;

		AnyEventEmitter::I().EmitEvent("SimulationStarted");
	}

	void SimulationControls::_PauseSimulation()
	{
		_isSimulating = true;

		AnyEventEmitter::I().EmitEvent("SimulationPaused");
	}

	void SimulationControls::_RefreshSimulation()
	{

		AnyEventEmitter::I().EmitEvent("RefreshSimulation");
	}
}