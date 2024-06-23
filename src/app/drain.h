#pragma once

#include "entity.h"

namespace simstudio {
	class Drain : public Entity {

	public:

		FactoryType("drain")


		static Shared<Drain> New();

	};
}