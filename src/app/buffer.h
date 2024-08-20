#pragma once

#include "entity.h"
#include "statistics/buffer_statistics.h"

namespace simstudio {

	class Buffer : public Entity {

	public:

		long _limit = 8;
		Array<Shared<Entity>> _buffer;

		BufferStatistics _statistics;

	public:

		FactoryType("buffer");

		static Shared<Buffer> New();

		virtual void Init();
		virtual void Step(World& app, Stepper& stepper) override;
		virtual void FromXml(SafeXmlNode& node) override;

		bool TakeEntity(Shared<Entity>& entity);
		bool CanTakeEntity();

		Shared<Entity> PopEntity();

		virtual void PrintFinalStatistics(long statistics_delay, long simulation_duration);



	};


}