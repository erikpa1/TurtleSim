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

	enum StationStates
	{
		NON_OPERATIVE,
		HANDICAPED,
		BLOCKED,
		WORKING

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
		String _warehouse;


		long _manufacturing_started = 0;

		StationStates _activeState = StationStates::NON_OPERATIVE;

		StationStatistics _statistics;

		Shared<Entity> _activeEntity;



	public:

		static Shared<Station> New();

		virtual void Init();
		virtual void Step() override;

		virtual void PrintFinalStatistics(long statistics_delay, long simulation_duration);

		virtual void FromXml(SafeXmlNode& node) override;
		virtual bool TakeEntity(Shared<Entity>& entity) override;
		virtual bool CanTakeEntity() override;

		int GetStateInt() override;



	private:
		void _StartManufacturing();
		void _FinishManufacturing();
		void _TryToPassNextEntity();

		bool _AddMaterialConsumption();

	};

};