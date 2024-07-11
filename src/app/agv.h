#pragma once
#include "entity.h"
#include "statistics/agv_statistics.h"


namespace simstudio {


	class Track;

	enum class AgvPowerType {
		ELECTRIC = 0,
		PETROL = 1,
	};


	class Agv : public Entity {

	public:
		FactoryType("agv");

		double _speed = 1;
		double _energy_consumption = 1;
		double _energy_storage = 100;

		AgvStatistics _statistics;



	public:
		static Shared<Agv>New();

		virtual String Type() override;

		virtual void Init() override;
		virtual void Step(App& app, Stepper& stepper) override;
		virtual void FromXml(SafeXmlNode& node) override;


		virtual void PrintFinalStatistics(long statistics_delay, long simulation_duration);
	};

}