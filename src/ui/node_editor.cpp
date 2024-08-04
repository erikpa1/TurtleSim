#include "node_editor.h"

#include "imgui/imgui.h"






namespace simstudio {


	NodeEditor::NodeEditor()
	{
		_context = ed::CreateEditor(&_config);

	}

	void NodeEditor::_DrawNode(const String& nodeName)
	{
		static int uniqueId = 1;
		// Start drawing nodes.
		ed::BeginNode(uniqueId++);
		//ed::SetNodePosition(uniqueId, ImVec2::ImVec2());
		ImGui::Text(nodeName.c_str());
		ed::BeginPin(uniqueId++, ed::PinKind::Input);
		ImGui::Text("-> In");
		ed::EndPin();
		ImGui::SameLine();
		ed::BeginPin(uniqueId++, ed::PinKind::Output);
		ImGui::Text("Out ->");
		ed::EndPin();
		ed::EndNode();
	}

	void NodeEditor::Draw()
	{

		auto& io = ImGui::GetIO();

		ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.0f / io.Framerate : 0.0f);

		ImGui::Separator();

		ed::SetCurrentEditor(_context);
		ed::Begin("My Editor", ImVec2(0.0, 0.0f));
		_DrawNode("Test node");
		_DrawNode("Test node 2");
		ed::End();
		ed::SetCurrentEditor(nullptr);



	}


}

