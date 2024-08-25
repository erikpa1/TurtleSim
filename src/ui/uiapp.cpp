#include "uiapp.h"


#include "node_editor.h"


#include "imgui/imgui.h"


#include "../app/world.h"

namespace simstudio {

	UiApp::UiApp()
	{

		_world = Share<World>();

		_appControls._app = this;
		_hierarchy._app = this;
		_avlEntities._app = this;

		_entityProperties.SetApp(this);
	}

	void UiApp::StartDrawing()
	{

		ImGui::NewFrame();


		ImGui::DockSpace(ImGui::GetID("Dockspace"), ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

		_DrawOverlay();


		_appControls.Draw();

		ImGui::Begin("Root", &_leftBarActive); ImGui::End();


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

		_hierarchy.Draw();
		_nodeEditor.Draw();


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

	void UiApp::_CreateDefaultLayout()
	{


	}

	void UiApp::_DrawOverlay()
	{
		ImVec2 display_size = ImGui::GetIO().DisplaySize;
		float screen_width = display_size.x;
		float screen_height = display_size.y;

		//ImGui::SetNextWindowPos(ImVec2(0, 0)); // Set window position to top-left corner
		//ImGui::SetNextWindowSize(ImVec2(screen_width, screen_height)); // Make the window size equal to screen size
		// ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
		ImGui::Begin("Root");
		//ImGui::Begin("Root", nullptr, ImGuiWindowFlags_NoTitleBar  | ImGuiWindowFlags_NoBackground);

		// Your ImGui drawing code here, e.g., rendering a HUD, overlay, etc.

		ImGui::End();
	}


}
