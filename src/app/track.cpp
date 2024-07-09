#include "track.h"

#include "../serialization/prelude.h"

namespace simstudio {

	void Track::FromXml(SafeXmlNode& node)
	{
		Entity::FromXml(node);
		_length = node.GetIntAttrib("length", 1);
	}
}
