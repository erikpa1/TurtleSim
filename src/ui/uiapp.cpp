#include "uiapp.h"


#include "node_editor.h"


#include "../../external/imgui/imgui.h"


namespace simstudio {

	UiApp::UiApp()
	{
		_appControls._app = this;
		_hierarchy._app = this;
		_avlEntities._app = this;
		_entityProperties._app = this;
	}

	void UiApp::StartDrawing()
	{

		ImGui::NewFrame();

		_appControls.Draw();

		if (_app) {
			_DrawLeftBar();
			_DrawMiddleBar();
			_DrawRightBar();
		}


		// Rendering
		ImGui::Render();
		ImGui::UpdatePlatformWindows();



	}
	void UiApp::_DrawLeftBar()
	{
		ImGui::Begin("Available entities", &_leftBarActive, ImGuiWindowFlags_MenuBar);


		_avlEntities.Draw();

		//Ending begin
		ImGui::End();
	}

	void UiApp::_DrawMiddleBar()
	{
		ImGui::Begin("Canvas", &_leftBarActive, ImGuiWindowFlags_MenuBar);

		ImGui::Text("This is place for you nodes");

		NodeEditor::Draw();
		_hierarchy.Draw();

		//Ending begin
		ImGui::End();

	}

	void UiApp::_DrawRightBar()
	{
		ImGui::Begin("Properties", &_leftBarActive);

		_entityProperties.Draw();

		//Ending begin
		ImGui::End();
	}


}
