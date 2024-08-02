#include "app_controls.h"




#include "../../external/imgui/imgui.h"

#include "uiapp.h"

#include "../app/app.h"


void simstudio::AppControls::Draw()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Project"))
		{


			bool canSave = _app->_app ? true : false;

			if (ImGui::MenuItem("Save", "CTRL+S", nullptr, canSave)) {

			}

			if (ImGui::MenuItem("New", "CTRL+N")) {
				_StartNewProject();
			}
			if (ImGui::MenuItem("Open")) {
				_OpenProject();
			}

			if (ImGui::MenuItem("Recent")) {

			}

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void simstudio::AppControls::_StartNewProject()
{
	_app->_app = Share<App>();
}

void simstudio::AppControls::_OpenProject()
{
}



