

#include "class_factory.h"

namespace simstudio {

	void ClassFactory::RegisterConstructor(String type, ConstructFunction function)
	{
		_constructors[type] = function;
	}
}