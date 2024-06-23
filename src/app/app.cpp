

#include "app.h"
#include "entity.h"

#include "stepper.h"
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
		for (long i = 0; i < 100; i++) {
			Step();
		}
	}

	void App::Step()
	{
		for (const auto& iter : _entities)
		{
			auto &entity = iter.second;
			entity->_activeTime = _stepper._stepIndex;
		}

		for (const auto& iter : _entities)
		{
			auto &entity = iter.second;

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
			iter.second->PrintFinalStatistics();
		}
	}

}