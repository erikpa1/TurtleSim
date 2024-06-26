#pragma once
#include "entity.h"
#include "anynumber.h"

#include "statistics/source_statistics.h"

namespace simstudio {

	class Stepper;
	class App;
	class SafeXmlNode;

	class Source : public Entity {

	public:
		FactoryType("source");

		AnyNumber _spawn_time;

		long _nextAction = LONG_MAX;

		Shared<Entity> _activeEntity;


	public:
		static Shared<Source> New();

		virtual String Type() override;

		virtual void Init() override;
		virtual void Step(App& app, Stepper& stepper) override;
		virtual void FromXml(SafeXmlNode& node) override;

		SourceStatistics _statistics;

	private:

		void _CalculateNextAction(long currentTime);
		void _TryMoveEntityNext(App& app);
	};

}