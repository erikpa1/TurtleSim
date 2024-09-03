#include "uiapp.h"


#include "node_editor.h"


#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"


#include "../app/world.h"

void SetupDockingLayout()
{
	ImGuiID dockspace_id = ImGui::GetID("MyDockspace");

	ImGui::DockBuilderRemoveNode(dockspace_id); // Clear any existing layout
	ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace); // Create new docking node

	ImGuiID dock_main_id = dockspace_id;
	ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, nullptr, &dock_main_id);
	ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.20f, nullptr, &dock_main_id);

	// Dock the windows
	ImGui::DockBuilderDockWindow("Hierarchy", dock_id_left);
	ImGui::DockBuilderDockWindow("Inspector", dock_id_right);
	ImGui::DockBuilderDockWindow("Scene", dock_main_id);

	ImGui::DockBuilderFinish(dockspace_id); // Finish building the layout
}

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
		//ImGui::NewFrame();
		//_DrawDock();
		// Rendering
		//ImGui::Render();
		//ImGui::UpdatePlatformWindows();
		//return;

		ImGui::NewFrame();



		_DrawOverlay();


		_appControls.Draw();

		ImGui::Begin("Root", &_leftBarActive);

		ImGui::DockSpace(ImGui::GetID("Root"), ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode); ImGui::End();

		if (_world) {
			_DrawLeftBar();
			_DrawMiddleBar();
			_DrawRightBar();
		}


		// Rendering
		ImGui::Render();
		ImGui::UpdatePlatformWindows();



	}
	void UiApp::_DrawDock()
	{

		// Set window flags (optional)
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;


		static bool isFirst = true;


		if (isFirst) {
			isFirst = false;

			auto tmpSize = ImGui::GetIO().DisplaySize;
			tmpSize.x = tmpSize.x / 2;
			tmpSize.y = tmpSize.y / 2;
			// Create a full-screen window for the docking space

			ImGui::SetNextWindowPos(ImVec2(40, 40));
			ImGui::SetNextWindowSize(tmpSize);


		}


		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::Begin("DockSpace Demo", nullptr, window_flags);
		ImGui::PopStyleVar(2);

		// Create the actual dock space
		ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

		ImGuiID parent_node = ImGui::DockBuilderAddNode();
		ImGui::DockBuilderSetNodePos(parent_node, ImGui::GetWindowPos());
		ImGui::DockBuilderSetNodeSize(parent_node, ImGui::GetWindowSize());
		ImGuiID nodeA;
		ImGuiID nodeB;
		ImGui::DockBuilderSplitNode(parent_node, ImGuiDir_Up, 0.8f, &nodeB, &nodeA);

		ImGui::DockBuilderDockWindow("A", nodeA);
		ImGui::DockBuilderDockWindow("B", nodeB);


		ImGui::End();


		ImGui::SetNextWindowDockID(nodeA, ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(200, 600));
		ImGui::Begin("Hierarchy");
		ImGui::Text("This is the Hierarchy panel.");
		ImGui::End();

		ImGui::SetNextWindowDockID(nodeB, ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(200, 600));
		ImGui::Begin("Inspector");
		ImGui::Text("This is the Inspector panel.");
		ImGui::End();

		ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(800, 600));
		ImGui::Begin("Scene");
		ImGui::Text("This is the Scene view.");
		ImGui::End();


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
