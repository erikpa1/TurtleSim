#pragma once
#include "entity.h"

namespace simstudio {


	enum class LoaderState {
		IDLE = 0,
		LOADING = 1,
		BROKEN = 2
	};

	class Loader : public Entity {



	public:
		FactoryType("loader");
		FactoryNew(Loader);

		String _targetBuffer = "";

		String _unloading_time = "00:00";

		long _unloading_started = 0;

		long _unloading_end = LONG_MAX;

		Shared<Entity> _activeEntity;

	public:

		virtual bool TakeEntity(Shared<Entity>& entity) override;
		virtual void Step(App& app, Stepper& stepper) override;
		virtual void FromXml(SafeXmlNode& node) override;

	private:

		void _TryPickEntryEntity();

	};


}