#pragma once

#include "imgui_blueprints/imgui_node_editor.h"
#include "SimCore/Prelude.h"


namespace ed = ax::NodeEditor;

namespace simstudio {

	class UiApp;
	class SimulationControls;
	class SimStates;

	class NodeEditor {

	public:

		NodeEditor();

		void SetApp(UiApp* app);
		void Draw();
		void Update();

		ed::Config _config;
		ed::EditorContext* _context;

	private:

		UiApp* _app;

		Shared<SimulationControls> _controls;
		Shared<SimStates> _states;

		void _DrawNode(const String& nodeName);

	};

}