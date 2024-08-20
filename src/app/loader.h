#pragma once
#include "entity.h"

#include "statistics/loader_statistics.h"

namespace simstudio {


	enum class LoaderState {
		IDLE = 0,
		LOADING = 1,
		BLOCKED = 2,
		BLOCKED_AGV = 3,
		BROKEN = 4
	};

	class Loader : public Entity {



	public:
		FactoryType("loader");
		FactoryNew(Loader);

		String _targetBuffer = "";

		String _loading_time = "00:00";

		long _loading_started = 0;

		long _loading_end = LONG_MAX;

		Shared<Entity> _activeEntity;
		Shared<Entity> _handledEntity;

		LoaderState _activeState;

		LoaderStatistics _statistics;

	public:

		virtual bool TakeEntity(Shared<Entity>& entity) override;
		virtual void Step(World& app, Stepper& stepper) override;
		virtual void FromXml(SafeXmlNode& node) override;

		virtual void PrintFinalStatistics(long statistics_delay, long simulation_duration);


	private:


		void _StartPicking();
		void _TryPickEntryEntity();

		void _LoadActiveEntityAndLetGo();
		void _TryUnblock();

		bool _TrySendAgvNext();

	};


}