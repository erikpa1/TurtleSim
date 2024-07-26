#include "uiapp.h"

#include "available_entities_list.h"
#include "node_editor.h"


#include "../../external/imgui/imgui.h"



namespace simstudio {

	void UiApp::StartDrawing()
	{

		ImGui::NewFrame();

		_DrawLeftBar();
		_DrawMiddleBar();
		_DrawRightBar();


		// Rendering
		ImGui::Render();
		ImGui::UpdatePlatformWindows();



	}
	void UiApp::_DrawLeftBar()
	{
		ImGui::Begin("Available entities", &_leftBarActive, ImGuiWindowFlags_MenuBar);


		AvailableEntitiesList::Draw();


		//Ending begin
		ImGui::End();
	}

	void UiApp::_DrawMiddleBar()
	{
		ImGui::Begin("Canvas", &_leftBarActive, ImGuiWindowFlags_MenuBar);

		ImGui::Text("This is place for you nodes");

		NodeEditor::Draw();

		//Ending begin
		ImGui::End();

	}

	void UiApp::_DrawRightBar()
	{
		ImGui::Begin("Properties", &_leftBarActive);

		ImGui::Text("This is place for your properties");

		//Ending begin
		ImGui::End();
	}
}
