#pragma once
#include "../prelude.h"

#include "stepper.h"

namespace simstudio
{

	class Entity;

	class App
	{
	public:
		App();

		HashMap<Shared<Entity>> _entities;

		HashMap<String> _connections;

		Stepper _stepper;

		void Init();

		void PrintEntities();

		void StartSimulation();

		void Step();
		void AddEntity(Shared<Entity> entity);

		void AddEntityConnection(String connA, String connB);

		bool MoveEntity(Shared<Entity> &entity, String fromEntity, String toEntity);


		void PrintFinalStatistics();

		void LoadFromXmlFile(const String& path);
	};

};