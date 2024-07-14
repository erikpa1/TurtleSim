#include "unloader.h"

#include "stepper.h"
#include "app.h"

#include "../utils/time_expr.h"

#include "../serialization/prelude.h"


namespace simstudio {

	bool Unloader::TakeEntity(Shared<Entity>& entity)
	{
		if (_activeEntity) {
			return false;
		}
		else {
			_activeEntity = entity;
			return true;
		}
	}



	void Unloader::Step(App& app, Stepper& stepper)
	{


	}

	void Unloader::FromXml(SafeXmlNode& node)
	{
		Entity::FromXml(node);

	}

	void Unloader::_StartUnloading(Stepper& stepper)
	{
		_unloading_started = stepper.GetStepSecond();
		_unloading_end = _unloading_started + TimeExpr::SecondsFromTimeString(_unloading_time);




	}



}