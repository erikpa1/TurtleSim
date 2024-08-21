#include "uiapp.h"


#include "node_editor.h"


#include "imgui/imgui.h"


namespace simstudio {

	UiApp::UiApp()
	{
		_appControls._app = this;
		_hierarchy._app = this;
		_avlEntities._app = this;

		_entityProperties.SetApp(this);
	}

	void UiApp::StartDrawing()
	{

		ImGui::NewFrame();

		_appControls.Draw();

		if (_world) {
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


		// Retrieve the current viewport
		//ImGuiViewport* viewport = ImGui::GetMainViewport();

		// Set the next window position to the top-left corner of the viewport
		//ImGui::SetNextWindowPos(viewport->Pos);

		// Set the next window size to match the viewport size
		//ImGui::SetNextWindowSize(viewport->Size);

		// Optionally remove title bar, borders, and other window decorations
		//ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
		//	ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
		//	ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;


		ImGui::Begin("Canvas", &_leftBarActive, ImGuiWindowFlags_MenuBar);

		ImGui::Text("This is place for you nodes");

		_nodeEditor.Draw();
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

		ImGui::Begin("Console", &_leftBarActive);
		_console.Draw();
		ImGui::End();
	

	}


}
