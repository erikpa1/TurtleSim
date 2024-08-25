#include "app_controls.h"

#include "uiapp.h"

#include "components/FileDialog.h"

#include "imgui/imgui.h"

#include "../app/world.h"

#include "../serialization/safejson.h"

namespace simstudio {
	void AppControls::Draw()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Project"))
			{

				if (ImGui::MenuItem("Open")) {
					_OpenProject();
				}

				bool canSave = _app->_world ? true : false;

				if (ImGui::MenuItem("Save", "CTRL+S", nullptr, canSave)) {
					_SaveProject();
				}

				if (ImGui::MenuItem("New", "CTRL+N")) {
					_StartNewProject();
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
		_app->_world = Share<World>();
	}

	void AppControls::_OpenProject()
	{
		const auto data = FileDialog::ReadFileString("");//FileDialog::GetJsonExtension()

		if (data != "") {
			SafeJson json;
			json.ParseString(data);

			_app->_world = Share<World>();
			_app->_world->FromJson(json);
		}
	}

	void AppControls::_SaveProject()
	{
		SafeJson json;
		_app->_world->SaveToJson(json);

		FileDialog::SaveJsonFile(json.Dump(), ".simstudio.json");
	}




}

