#pragma once

#include "../app/app.h"

#include "entities_hierarchy.h"
#include "available_entities_list.h"
#include "entity_properties.h"


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



	public:
		Shared<App> _app;
		Shared<Entity> _activeEntity;

	};




};

