#include "unloader.h"

#include "stepper.h"
#include "world.h"

#include "../utils/time_expr.h"

#include "../serialization/prelude.h"


namespace simstudio {

	bool Unloader::CanTakeEntity()
	{
		return _activeEntity == nullptr;
	}

	bool Unloader::TakeEntity(Shared<Entity>& entity)
	{
		if (CanTakeEntity()) {
			LogE << "Taking agv to unload" << entity->_name;
			_activeEntity = entity;
			_StartUnloading();
			return true;
		}
		else {
			LogE << StringThis() << " can't take entity because is occupied.";
			return false;
		}

	}



	void Unloader::Step(World& app, Stepper& stepper)
	{
		if (_activeState == UnloaderState::WORKING) {
			if (_unloading_end <= GetSimSecond()) {
				_UnloadingFinished();
			}
		}
		else if (_activeState == UnloaderState::BLOCKED) {
			_statistics._blocked += GetLastStepOffset();
			_StartUnloading();
		}

	}

	void Unloader::FromXml(SafeXmlNode& node)
	{
		Entity::FromXml(node);

		_unloading_time = node.GetStringAttrib("operation_time", "00:00");
		_targetBuffer = node.GetStringAttrib("target_buffer", "");

	}

	void Unloader::PrintFinalStatistics(long statistics_delay, long simulation_duration)
	{
		LogD << "======================";
		LogD << F("Final statistics for Unloader [{}]", _uid);
		LogI << "Unloaded: " << _statistics._unloaded;
	}

	void Unloader::_UnloadingFinished()
	{

		if (_world->_entities.contains(_targetBuffer)) {

			if (_handledEntity) {
				auto target = _world->_entities[_targetBuffer];

				if (target->TakeEntity(_handledEntity)) {
					_handledEntity.reset();
					_statistics._unloaded += 1;

					_StartUnloading();
				}
				else {
					_activeState = UnloaderState::IDLE;
					LogE << StringThis() << " is blocked because of target is busy";
				}



			}
		}
		else {
			_activeState = UnloaderState::BLOCKED;
			LogE << StringThis() << " is blocked because of invalid target";
		}



	}

	void Unloader::_TryToPassNextEntity()
	{
		if (_activeEntity) {
			auto connections = GetConnections();

			for (const auto& connection : connections) {
				if (connection->TakeEntity(_activeEntity)) {
					_activeEntity.reset();
					break;
				}
			}
		}

	}

	void Unloader::_StartUnloading()
	{
		if (_activeEntity) {
			if (_activeEntity->ChildrenCount() > 0) {
				_activeState = UnloaderState::WORKING;

				_handledEntity = _activeEntity->PopChildEntity();
				_unloading_started = GetSimSecond();
				_unloading_end = _unloading_started + TimeExpr::SecondsFromTimeString(_unloading_time);

			}
			else {
				_TryToPassNextEntity();
			}
		}
	}





}