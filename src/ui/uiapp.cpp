#include "uiapp.h"


#include "node_editor.h"


#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"


#include "../app/world.h"

#include "../utils/exe_dir.h"


#include <fstream>

#include "imguiini.h"

namespace simstudio {


	void UiApp::LoadDefaultImguiIni()
	{
		const  String initFile = F("{}\\{}", GetExecutionDirectory(), "imgui.ini");

		std::ifstream f(initFile.c_str());

		if (f.good() == false) {
			std::ofstream outFile(initFile);

			if (!outFile) {
				LogE << "Error opening file for writing: " << initFile;
			}
			else {
				outFile << INIF_FILE;
				outFile.close();
			}

			LogD << "Created Imgui INI file";
		}



	}


	UiApp::UiApp()
	{

		_world = Share<World>();

		_appControls._app = this;
		_hierarchy._app = this;
		_avlEntities._app = this;

		_nodeEditor.SetApp(this);
		_entityProperties.SetApp(this);
	}

	void UiApp::Draw()
	{
		//ImGui::NewFrame();
		//_DrawDock();
		// Rendering
		//ImGui::Render();
		//ImGui::UpdatePlatformWindows();
		//return;

		ImGui::NewFrame();

		_appControls.Draw();

		_DrawOverlay();



		if (_world) {
			_DrawLeftBar();
			_DrawMiddleBar();
			_DrawRightBar();
		}

		// Rendering
		ImGui::Render();
		ImGui::UpdatePlatformWindows();

	}

	void UiApp::Update()
	{
		_nodeEditor.Update();
	}

	void UiApp::AfterImguiInit()
	{
		//Premena musi byt static, pretoze c_str neprezije destrukciu stringu....
		static const String initFile = F("{}\\{}", GetExecutionDirectory(), "imgui.ini");
		ImGui::GetIO().IniFilename = initFile.c_str();
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

		const auto paddings = ImGui::GetStyle().FramePadding;

		float menuBarHeight = (paddings.y * 2.0f + ImGui::GetFontSize()) / 2;

		float screen_width = display_size.x;
		float screen_height = display_size.y;

		ImGui::SetNextWindowPos(ImVec2(0 - (paddings.x * 2), 0 + menuBarHeight)); // Set window position to top-left corner
		ImGui::SetNextWindowSize(ImVec2(screen_width + (paddings.x * 4), screen_height)); // Make the window size equal to screen size
		//ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
		//ImGui::Begin("Root");
		const auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		ImGui::Begin("Root", nullptr, flags);

		// Your ImGui drawing code here, e.g., rendering a HUD, overlay, etc.

		ImGui::DockSpace(ImGui::GetID("Root"), ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
		ImGui::End();
	}


}
