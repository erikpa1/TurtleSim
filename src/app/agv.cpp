#include "agv.h"

#include "app.h"
#include "stepper.h"
#include "track.h"

#include "../serialization/prelude.h"

namespace simstudio {


	Shared<Agv> Agv::New()
	{
		return Share<Agv>();
	}

	void Agv::Init()
	{
	}

	void Agv::Step(App& app, Stepper& stepper)
	{

	}

	void Agv::FromXml(SafeXmlNode& node)
	{
		Entity::FromXml(node);
	}

	bool Agv::TakeEntity(Shared<Entity>& entity)
	{
		if (CanTakeEntity()) {
			_buffer.push_back(entity);
			return true;
		}

		return false;

	}

	bool Agv::CanTakeEntity()
	{
		return _buffer.size() <= _limit;
	}

	void Agv::PrintFinalStatistics(long statistics_delay, long simulation_duration)
	{
		LogD << "======================";
		LogD << F("Final statistics for Agv [{}]", _uid);
		LogI << "Agv valked:" << _statistics.walked << " m";
	}


	Shared<Entity> Agv::PopChildEntity()
	{
		Shared<Entity> _poped_entity = _buffer.back();
		_buffer.pop_back();
		return _poped_entity;
	}

	int Agv::ChildrenCount()
	{
		return _buffer.size();
	}




}