#include "loader.h"

#include "world.h"
#include "buffer.h"
#include "stepper.h"

#include "../utils/time_expr.h"

#include "../serialization/safexml.h"

namespace simstudio {


	bool Loader::TakeEntity(Shared<Entity>& entity)
	{
		if (_activeEntity) {
			return false;
		}
		else {
			LogE << "Loader is taking entity";
			_activeEntity = entity;
			_StartPicking();
			return true;
		}

	}
	void Loader::Step()
	{
		if (_activeState == LoaderState::LOADING) {
			_statistics._worked += GetLastStepOffset();
			if (_loading_end <= GetSimSecond()) {
				_LoadActiveEntityAndLetGo();
			}
		}
		else if (_activeState == LoaderState::BLOCKED) {
			_statistics._blocked += GetLastStepOffset();
			_LoadActiveEntityAndLetGo();
		}
		else if (_activeState == LoaderState::IDLE) {
			_statistics._idle += GetLastStepOffset();
		}
	}

	void Loader::FromXml(SafeXmlNode& node)
	{
		Entity::FromXml(node);

		_loading_time = node.GetStringAttrib("operation_time", "");
		_targetBuffer = node.GetStringAttrib("target_buffer", "");
	}

	void Loader::PrintFinalStatistics(long statistics_delay, long simulation_duration)
	{
		LogD << "======================";
		LogD << F("Final statistics for Loader [{}]", _uid);

		double blocked_percentage = (static_cast<double>(_statistics._blocked) / static_cast<double>(simulation_duration));
		double idle_percentage = (static_cast<double>(_statistics._idle) / static_cast<double>(simulation_duration));
		double working_percentage = (static_cast<double>(_statistics._idle) / static_cast<double>(simulation_duration));

		LogI << "Loaded: " << _statistics._loaded;
		LogI << "Blocked: " << blocked_percentage * 100 << "%";
		LogI << "Idle: " << idle_percentage * 100 << "%";
		LogI << "Working: " << working_percentage * 100 << "%";


	}

	void Loader::_StartPicking()
	{
		if (_handledEntity == nullptr) {
			if (_activeEntity) {
				if (_world) {

					if (_world->_entities.contains(_targetBuffer)) {
						Shared<Buffer> _buffer = StaticCast<Buffer>(_world->_entities[_targetBuffer]);

						if (_buffer) {
							auto buffer = _buffer->PopEntity();
							if (buffer) {
								_handledEntity = buffer;

								_activeState = LoaderState::LOADING;

								_loading_started = GetSimSecond();
								_loading_end = _loading_started + TimeExpr::SecondsFromTimeString(_loading_time);

								LogE << "Loader going finish unloading at: " << _loading_end;

							}
						}
					}
				}
			}

		}

	}

	void Loader::_TryPickEntryEntity()
	{

	}
	void Loader::_LoadActiveEntityAndLetGo()
	{

		if (_activeEntity && _handledEntity) {

			if (_activeEntity->TakeEntity(_handledEntity)) {
				_statistics._loaded += 1;
				_handledEntity.reset();

				LogI << StringThis() << "loaded AGV [" << _activeEntity->_uid << "]";
				_TrySendAgvNext();

			}
			else {
				LogI << StringThis() << "blocked because AGV can't take entity";
				_activeState = LoaderState::BLOCKED;
			}
		}
		else {
			LogI << StringThis() << "blocked because AGV is not there";
			_activeState = LoaderState::BLOCKED;
		}
	}
	void Loader::_TryUnblock()
	{

		if (_handledEntity == nullptr && _activeEntity) {
			_TrySendAgvNext();
		}
		else if (_handledEntity && _activeEntity) {
			_LoadActiveEntityAndLetGo();
		}
	}
	bool Loader::_TrySendAgvNext()
	{
		auto connections = GetConnections();

		bool taken = false;

		for (const auto& conn : connections) {
			if (conn->TakeEntity(_activeEntity)) {
				LogI << StringThis() << "moved AGV [" << _activeEntity->_uid << "]";
				_activeEntity.reset();
				_activeState = LoaderState::IDLE;
				taken = true;
				break;
			}
		}

		if (taken == false) {
			LogE << StringThis() << "couldn't move AGV next";
			_activeState = LoaderState::BLOCKED;
		}

		return taken;
	}
}