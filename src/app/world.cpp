

#include "world.h"
#include "entity.h"

#include "stepper.h"

#include "../utils/class_factory.h"
#include "../utils/time_expr.h"

//TODO toto zaobalit na kompletku
#include "../external/tinyxml2.h"
#include "../serialization/safexml.h"

#include "../serialization/safejson.h"





namespace simstudio
{

	World::World()
	{
		//TODO dorobit custom entities template
		_stepper = Stepper();
	}

	void World::Init()
	{
		for (const auto& iter : _entities)
		{
			iter.second->Init();
		}
	}

	void World::PrintEntities()
	{
		for (const auto& iter : _entities)
		{
			LogI << iter.second->_uid;
		}
	}

	void World::StartSimulation()
	{
		LogD << "Starting simulation with duration: " << _stepper._endIndex;

		for (long i = 0; i <= _stepper._endIndex; i++) {
			Step();
		}
	}

	void World::Step()
	{
		_stepper.Step();

		for (const auto& iter : _entities)
		{
			auto& entity = iter.second;
			entity->_activeTime = _stepper._stepIndex;
		}

		for (const auto& iter : _entities)
		{
			auto& entity = iter.second;

			entity->Step(*this, _stepper);
		}

	}

	void World::AddEntity(Shared<Entity> entity)
	{
		_entities[entity->_uid] = entity;
	}

	Shared<Entity> World::SpawnEntity(std::function<Shared<Entity>()> fn)
	{
		Shared<Entity> tmp = fn();
		tmp->_weakThis = tmp;
		return tmp;

	}

	void World::UnlinkEntity(const String& uid)
	{
		if (_spawnies.contains(uid)) {
			_spawnies.erase(uid);
		}
	}

	void World::AddSpawnedEntity(Shared<Entity>& entity)
	{
		_spawnies[entity->_uid] = entity;
	}

	void World::AddEntityConnection(String connA, String connB)
	{
		if (_connections.contains(connA)) {
			_connections[connA].push_back(connB);
		}
		else {
			_connections[connA] = { connB };
		}

	}

	bool World::MoveEntity(Shared<Entity>& entity, String fromEntity, String toEntity)
	{
		LogD << "Moving entity from: " << fromEntity << " to " << toEntity;

		if (_connections.find(toEntity) != _connections.end()) {
			return _entities[toEntity]->TakeEntity(entity);
		}
		return false;
	}



	void World::LoadFromXmlString(const String& xmlString)
	{
		SafeXml doc;
		doc.LoadString(xmlString);
		LoadFromSafeXmlNode(doc);
	}

	void World::LoadFromXmlFile(const String& path)
	{


		SafeXml doc;
		doc.LoadFile(path);
		LoadFromSafeXmlNode(doc);


	}

	void World::LoadFromSafeXmlNode(SafeXml& doc)
	{

		auto factory = ClassFactory::Instance();


		if (doc.ErrorID() == 0) {

			auto app_root = doc._document->FirstChildElement("app");


			if (app_root) {

				LogE << app_root->ChildElementCount();

				auto simparams = app_root->FirstChildElement("simparams");

				if (simparams) {
					SafeXmlNode safe_sim_params(simparams);
					auto time_param = safe_sim_params.GetStringAttrib("simtime", "2:00");
					_stepper._endIndex = TimeExpr::SecondsFromTimeString(time_param);
				}

				auto entities = app_root->FirstChildElement("entities");


				if (entities) {

					for (auto child = entities->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {

						LogE << "Loading entity" << child->Name();

						auto child_type = child->Name();

						SafeXmlNode safe_child(child);

						auto child_name = safe_child.GetStringAttrib("name");
						auto child_uid = safe_child.GetStringAttrib("uid");

						auto entity = factory->Construct<Entity>(child_type);
						entity->_weakThis = entity;
						entity->FromXml(safe_child);
						entity->_world = this;
						AddEntity(entity);

					}
				}
				else {
					LogE << "Entities was invalid";
				}

				auto connections = app_root->FirstChildElement("connections");

				if (connections) {
					for (auto child = connections->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
						SafeXmlNode connection(child);

						auto a = connection.GetStringAttrib("a");
						auto b = connection.GetStringAttrib("b");

						if (a != "" && b != "") {
							AddEntityConnection(a, b);
						}
						else {
							LogE << "Incomplete connection, " << a << " " << b;
						}
					}

				}
				else {
					LogE << "Connections was invalid";
				}

				auto factory = ClassFactory::Instance();
			}
		}
		else {
			LogE << "Failed to open XML error id: " << doc.ErrorID();;
		}
	}




	Array<Shared<Entity>> World::GetConnectedEntities(const String& who)
	{
		Array<Shared<Entity>> successors;

		if (_connections.contains(who)) {

			auto successor_uids = _connections[who];

			for (const auto& successor_uid : successor_uids) {
				if (_entities.contains(successor_uid)) {
					successors.push_back(_entities[successor_uid]);
				}
			}
		}
		return successors;

	}

	void World::FromJson(SafeJson& jobj)
	{
		auto factory = ClassFactory::Instance();

		const auto entities = jobj.GetObjectArray("entities");

		LogE << entities.size();

		for (const auto& entity_json : entities) {
			auto child_type = entity_json->GetString("type", "entity");

			auto entity = factory->Construct<Entity>(child_type);
			entity->_weakThis = entity;
			entity->FromJson(entity_json);
			entity->_world = this;
			AddEntity(entity);

		}

	}

	void World::SaveToJson(SafeJson& jobj)
	{
		jobj.WriteString("name", "Some model");
		jobj.WriteString("uid", "0001-3322-3949");
		jobj.WriteString("created_at", "now");
		jobj.WriteString("last_save", "tommoroow");

		SafeJson entities;

		Array<Shared<SafeJson>> entities_jarray;

		for (const auto& iter : this->_entities) {
			entities_jarray.push_back(iter.second->ToJson());

		}

		jobj.WriteJsonArray("entities", entities_jarray);

	}

}