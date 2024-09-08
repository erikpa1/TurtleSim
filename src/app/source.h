#pragma once
#include "entity.h"
#include "anynumber.h"

#include "statistics/source_statistics.h"

namespace simstudio {

	class Stepper;
	class App;
	class SafeXmlNode;


	enum class DistributionStrategy {
		ROUND_ROBIN
	};

	class Source : public Entity {

	public:
		FactoryType("source");

		AnyNumber _spawn_time;

		long _nextAction = LONG_MAX;
		long _spawnLimit = -1;
		long _spawnedCount = 0;

		int _roundRobinIndex = 0;

		String _spawnEntity;

		Shared<Entity> _activeEntity;


	public:
		static Shared<Source> New();

		virtual void Init() override;
		virtual void Step() override;
		virtual void AfterStep() override;
		virtual void FromXml(SafeXmlNode& node) override;

		SourceStatistics _statistics;

	private:

		void _CalculateNextAction();
		void _TryMoveEntityNext();


		Shared<Entity> _GetSpawningEntity();
	};

}