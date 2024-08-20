#pragma once
#include "../prelude.h"

#include "stepper.h"

namespace simstudio
{

	class Entity;
	class SafeXml;
	class SafeJson;

	class World
	{
	public:
		World();

		HashMap<Shared<Entity>> _entities;

		HashMap<Shared<Entity>> _spawnies;


		HashMap<Array<String>> _connections;

		Stepper _stepper;

		void Init();

		void PrintEntities();

		void StartSimulation();

		void Step();
		void AddEntity(Shared<Entity> entity);

		Shared<Entity> SpawnEntity(std::function<Shared<Entity>()> fn);
		void UnlinkEntity(const String& uid);

		void AddSpawnedEntity(Shared<Entity>& entity);



		void AddEntityConnection(String connA, String connB);

		bool MoveEntity(Shared<Entity>& entity, String fromEntity, String toEntity);



		Array<Shared<Entity>> GetConnectedEntities(const String& who);

	public:
		//Serializatoins
		void LoadFromXmlString(const String& xmlString);
		void LoadFromXmlFile(const String& path);
		void LoadFromSafeXmlNode(SafeXml& doc);

		void FromJson(SafeJson& jobj);

		void SaveToJson(SafeJson& jobj);



	};

};