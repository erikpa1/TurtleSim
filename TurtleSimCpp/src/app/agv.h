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

		long _limit = 8;

		AgvStatistics _statistics;

		Array<Shared<Entity>> _buffer;

	public:
		static Shared<Agv>New();


		virtual void Init() override;
		virtual void Step() override;
		virtual void FromXml(SafeXmlNode& node) override;

		virtual bool TakeEntity(Shared<Entity>& entity) override;
		virtual bool CanTakeEntity() override;

		virtual void PrintFinalStatistics(long statistics_delay, long simulation_duration);


		virtual Shared<Entity> PopChildEntity();

		virtual int ChildrenCount();



	};

}