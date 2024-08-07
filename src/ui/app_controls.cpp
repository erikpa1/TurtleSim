#include "app_controls.h"

#include "uiapp.h"

#include "components/FileDialog.h"

#include "imgui/imgui.h"

#include "../app/app.h"

#include "../serialization/safejson.h"

namespace simstudio {
	void AppControls::Draw()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Project"))
			{


				bool canSave = _app->_app ? true : false;

				if (ImGui::MenuItem("Save", "CTRL+S", nullptr, canSave)) {
					_SaveProject();
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

	void AppControls::_StartNewProject()
	{
		_app->_app = Share<App>();
	}

	void AppControls::_OpenProject()
	{
	}

	void AppControls::_SaveProject()
	{
		SafeJson json;
		_app->_app->SaveToJson(json);
		FileDialog::SaveJsonFile(json.Dump());
	}




}

