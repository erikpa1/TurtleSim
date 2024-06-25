#pragma once

#include "entity.h"
#include "anynumber.h"

#include "statistics/station_statistics.h"

namespace simstudio
{

	class Stepper;
	class App;
	class Mu;

	class SafeXmlNode;

	enum StationNotEnoughEntitiesMode
	{
		NON_OPERATIVE,
		HANDICAPED

	};


	class Station : public Entity
	{

	public:

		FactoryType("station");
		~Station();

	public:


		AnyNumber _any_operation_time;

		long _manufacturing_end = LONG_MAX;

		String _operation_time_input = "00:00";

		bool _is_manufacturing = false;
		long _manufacturing_started = 0;

		StationNotEnoughEntitiesMode _not_enought_entities_mode = StationNotEnoughEntitiesMode::NON_OPERATIVE;

		StationStatistics _statistics;

		Shared<Entity> _activeEntity;



	public:

		static Shared<Station> New();

		String Type();

		virtual void Init();
		virtual void Step(App& app, Stepper& stepper) override;

		virtual void PrintFinalStatistics(long statistics_delay, long simulation_duration);

		virtual void FromXml(SafeXmlNode& node) override;
		virtual bool TakeEntity(Shared<Entity>& entity) override;
		virtual bool CanTakeEntity() override;

	private:
		void _StartManufacturing();

	};

};