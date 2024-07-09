#pragma once
#include "entity.h"

namespace simstudio {

	class Unloader : public Entity {

	public:
		FactoryType("unloader");
		FactoryNew(Unloader);

		long processing_time = 1;

	public:

		virtual void FromXml(SafeXmlNode& node) override;


	};

}