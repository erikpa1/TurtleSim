#pragma once
#include "entity.h"

#include "statistics/drain_statistics.h"

namespace simstudio {
	class Drain : public Entity {

	public:

		DrainStatistics _statistics;

	public:

		FactoryType("drain");


		static Shared<Drain> New();

		virtual bool TakeEntity(Shared<Entity>& entity) override;

		void PrintFinalStatistics(long start, long end) override;

	};
}