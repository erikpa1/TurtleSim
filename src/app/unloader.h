#pragma once
#include "entity.h"

namespace simstudio {


	enum class UnloaderStates {
		IDLE = 0,
		WORKING = 1
	};


	class Unloader : public Entity {

	public:
		FactoryType("unloader");
		FactoryNew(Unloader);

		String _targetBuffer = "";

		String _unloading_time = "00:00";

		long _unloading_started = 0;

		long _unloading_end = LONG_MAX;

		Shared<Entity> _activeEntity;

	public:

		virtual bool TakeEntity(Shared<Entity>& entity) override;

		virtual void Step(App& app, Stepper& stepper) override;

		virtual void FromXml(SafeXmlNode& node) override;


		void _StartUnloading(Stepper& stepper);

	};

}