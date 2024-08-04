#pragma once


#include "imgui_blueprints/imgui_node_editor.h"
#include "../prelude.h"

namespace ed = ax::NodeEditor;

namespace simstudio {


	class NodeEditor {

	public:
		void Draw();

		NodeEditor();

		ed::Config _config;
		ed::EditorContext* _context;

	private:

		void _DrawNode(const String & nodeName);

	};

}