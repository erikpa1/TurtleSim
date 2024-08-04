#pragma once

#include "../app/app.h"

#include "entities_hierarchy.h"
#include "available_entities_list.h"
#include "entity_properties.h"
#include "app_controls.h"
#include "node_editor.h"

namespace simstudio {


	class UiApp {

	public:

		UiApp();

		void StartDrawing();

	private:

		bool _leftBarActive = true;

		void _DrawLeftBar();
		void _DrawMiddleBar();
		void _DrawRightBar();





		EntitiesHierarchy _hierarchy;
		AvailableEntitiesList _avlEntities;
		EntityPropertiesView _entityProperties;
		AppControls _appControls;
		NodeEditor _nodeEditor;


	public:
		Shared<App> _app;
		Shared<Entity> _activeEntity;

	};




};

