#pragma once
#include "entity.h"

namespace simstudio {


	class Track : public Entity {


	public:
		double _length = 1;




	public:

		virtual void FromXml(SafeXmlNode& node) override;






	};
}