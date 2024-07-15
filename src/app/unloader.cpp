#include "unloader.h"

#include "stepper.h"
#include "app.h"

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
			_activeEntity = entity;





			return true;
		}
		else {
			LogE << StringThis() << " can't take entity because is [manufacturing].";
			return false;
		}


	}



	void Unloader::Step(App& app, Stepper& stepper)
	{


	}

	void Unloader::FromXml(SafeXmlNode& node)
	{
		Entity::FromXml(node);

	}

	void Unloader::_UnloadingFinished()
	{
		_statistics._unloaded += 1;
		_activeState = UnloaderState::IDLE;
		_TryToPassNextEntity();

	}

	void Unloader::_TryToPassNextEntity()
	{
		bool isBlocked = true;

		auto connections = _app->GetConnectedEntities(_uid);

		for (const auto& connection : connections) {
			if (connection->TakeEntity(_activeEntity)) {
				_activeEntity.reset();



			}
		}

	}

	void Unloader::_StartUnloading(Stepper& stepper)
	{
		_unloading_started = stepper.GetStepSecond();
		_unloading_end = _unloading_started + TimeExpr::SecondsFromTimeString(_unloading_time);




	}



}