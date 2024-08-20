#pragma once
#include "entity.h"
#include "statistics/conveyor_statistics.h"

namespace simstudio {

	class Conveyor : public Entity {

	public:

		long _limit = -1;

		double _speed = 1;


		Array<Shared<Entity>> _buffer;

		ConveyorStatistics _statistics;

	public:
		FactoryType("conveyor");

		static Shared<Conveyor> New();

		virtual void Init();
		virtual void Step(World& app, Stepper& stepper) override;
		virtual void FromXml(SafeXmlNode& node) override;

		bool TakeEntity(Shared<Entity>& entity);
		bool CanTakeEntity();

		virtual void PrintFinalStatistics(long statistics_delay, long simulation_duration);




	};

}