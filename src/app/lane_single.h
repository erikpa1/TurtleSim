#pragma once
#include "track.h"

namespace simstudio {

	class Agv;

	class SingleLane : public Track, EnableShare<SingleLane> {

	public:
		FactoryType("single_lane");
		FactoryNew(SingleLane);

		Weak<Agv> _activeAgv;

		virtual void Init();

		virtual bool TakeEntity(Shared<Entity>& entity) override;
		virtual void Step(App& app, Stepper& stepper) override;


	};

}