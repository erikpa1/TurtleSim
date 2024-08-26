#pragma once

#include "../app/world.h"

#include "entities_hierarchy.h"
#include "ViewAvailableEntities.h"
#include "entity_properties.h"
#include "app_controls.h"
#include "node_editor.h"
#include "console.h"                  

namespace simstudio {


	class UiApp {

	public:

		UiApp();

		void StartDrawing();

	private:

		bool _leftBarActive = true;

		void _DrawDock();

		void _DrawLeftBar();
		void _DrawMiddleBar();
		void _DrawRightBar();





		EntitiesHierarchy _hierarchy;
		AvailableEntitiesList _avlEntities;
		EntityPropertiesView _entityProperties;
		AppControls _appControls;
		NodeEditor _nodeEditor;
		Console _console;


	public:
		Shared<World> _world;
		Shared<Entity> _activeEntity;


	private:

		void _CreateDefaultLayout();
		void _DrawOverlay();

		bool _isFirst = false;

	};




};

