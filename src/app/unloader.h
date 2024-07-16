#pragma once
#include "entity.h"

#include "statistics/unloader_statistics.h"

namespace simstudio {


	enum class UnloaderState {
		IDLE = 0,
		WORKING = 1,
		BLOCKED = 2
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
		Shared<Entity> _handledEntity;

		UnloaderStatistics _statistics;

		UnloaderState _activeState;

	public:


		virtual bool CanTakeEntity() override;

		virtual bool TakeEntity(Shared<Entity>& entity) override;

		virtual void Step(App& app, Stepper& stepper) override;

		virtual void FromXml(SafeXmlNode& node) override;

		void _UnloadingFinished();
		void _TryToPassNextEntity();

		void _StartUnloading();


	};

}