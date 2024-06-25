

#include "app.h"
#include "entity.h"

#include "stepper.h"

#include "../utils/class_factory.h"
#include "../utils/time_expr.h"

//TODO toto zaobalit na kompletku
#include "../external/tinyxml2.h"
#include "../serialization/safexml.h"


using namespace tinyxml2;


namespace simstudio
{

	App::App()
	{
		_stepper = Stepper();
	}

	void App::Init()
	{
		for (const auto& iter : _entities)
		{
			iter.second->Init();
		}
	}

	void App::PrintEntities()
	{
		for (const auto& iter : _entities)
		{
			LogI << iter.second->_uid;
		}
	}

	void App::StartSimulation()
	{
		LogD << "Starting simulation with duration: " << _stepper._endIndex;

		for (long i = 0; i <= _stepper._endIndex; i++) {
			Step();
		}
	}

	void App::Step()
	{
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
		_stepper.Step();
	}

	void App::AddEntity(Shared<Entity> entity)
	{
		_entities[entity->_uid] = entity;
	}

	void App::AddEntityConnection(String connA, String connB)
	{
		_connections[connA] = connB;
	}

	bool App::MoveEntity(Shared<Entity>& entity, String fromEntity, String toEntity)
	{
		LogD << "Moving entity from: " << fromEntity << " to " << toEntity;

		if (_connections.find(toEntity) != _connections.end()) {
			return _entities[toEntity]->TakeEntity(entity);
		}
		return false;
	}



	void App::PrintFinalStatistics()
	{
		LogI << "==============";
		LogI << "Final statistics:";
		for (const auto& iter : _entities)
		{
			iter.second->PrintFinalStatistics(0, _stepper._stepIndex);
		}
	}

	void App::LoadFromXmlFile(const String& path)
	{
		auto factory = ClassFactory::Instance();

		LogI << &factory;

		SafeXml doc;
		doc.LoadFile(path);

		if (doc.ErrorID() == 0) {

			auto node_app = doc._document->FirstChildElement("app");


			if (node_app) {


				auto simparams = node_app->FirstChildElement("simparams");

				if (simparams) {
					SafeXmlNode safe_sim_params(simparams);
					auto time_param = safe_sim_params.GetStringAttrib("simtime", "2:00");
					_stepper._endIndex = TimeExpr::SecondsFromTimeString(time_param);
				}


				auto entities = node_app->FirstChildElement("entities");

				if (entities) {

					for (auto child = entities->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {

						auto child_type = child->Name();

						SafeXmlNode safe_child(child);

						auto child_name = safe_child.GetStringAttrib("name");
						auto child_uid = safe_child.GetStringAttrib("uid");


						auto entity = factory->Construct<Entity>(child_type);
						entity->FromXml(safe_child);
						AddEntity(entity);

					}
				}
				else {
					LogE << "Entities was invalid";
				}

				auto connections = node_app->FirstChildElement("connections");

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

				LogI << &factory;
			}
		}
		else {
			LogE << "Failed to open XML error id: " << doc.ErrorID();;
		}


	}

}