#include "app_controls.h"

#include "uiapp.h"

#include "components/FileDialog.h"

#include "imgui/imgui.h"

#include "../app/world.h"

#include "../serialization/safejson.h"
#include "../serialization/safexml.h"

namespace simstudio {


	void AppControls::Draw()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Project"))
			{

				if (ImGui::MenuItem("Open JSON")) {
					_OpenProjectJSON();
				}
				if (ImGui::MenuItem("Open XML")) {
					_OpenProjectXML();
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

			auto& io = ImGui::GetIO();
			ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.0f / io.Framerate : 0.0f);


			ImGui::EndMainMenuBar();
		}
	}

	void AppControls::_StartNewProject()
	{
		_app->_world = Share<World>();
	}

	void AppControls::_OpenProjectJSON()
	{
		const auto data = FileDialog::ReadFileString(".json");//FileDialog::GetJsonExtension()

		if (data != "") {
			SafeJson json;
			json.ParseString(data);

			_app->_world = Share<World>();
			_app->_world->FromJson(json);

			LogI << "Successfully loaded from JSON";
		}
	}

	void AppControls::_OpenProjectXML()
	{
		const auto path = FileDialog::GetFilePath(".xml");//FileDialog::GetJsonExtension()
		LogE << path;
		if (path != "") {
			SafeXml xml;
			xml.LoadFile(path);

			_app->_world = Share<World>();
			_app->_world->LoadFromSafeXmlNode(xml);
			LogI << "Successfully loaded from XML";
		}
	}

	void AppControls::_SaveProject()
	{
		SafeJson json;
		_app->_world->SaveToJson(json);

		FileDialog::SaveJsonFile(json.Dump(), ".simstudio.json");
	}




}

