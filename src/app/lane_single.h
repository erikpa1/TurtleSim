#pragma once
#include "track.h"

namespace simstudio {

	class SingleLane : public Track {

	public:
		FactoryType("single_lane");
		FactoryNew(SingleLane);



	};

}