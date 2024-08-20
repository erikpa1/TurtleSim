#pragma once
#include "track.h"

#include "statistics/lane_statistics.h"

namespace simstudio {

	class Agv;

	class SingleLane : public Track, EnableShare<SingleLane> {

	public:
		FactoryType("single_lane");
		FactoryNew(SingleLane);

		Shared<Agv> _activeAgv;


		LaneStatistics _statistics;

	public:

		virtual void Init();

		virtual bool TakeEntity(Shared<Entity>& entity) override;
		virtual void Step(World& app, Stepper& stepper) override;

		virtual void EntityTaken(Shared<Entity>& entity) override;


		virtual void PrintFinalStatistics(long statistics_delay, long simulation_duration);



	};

}