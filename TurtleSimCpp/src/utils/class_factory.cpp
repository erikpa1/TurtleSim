

#include "class_factory.h"

namespace simstudio {


	ClassFactory* ClassFactory::_instance = nullptr;

	ClassFactory* ClassFactory::Instance()
	{
		if (!_instance) {
			LogD << "Constructing instance";
			_instance = new ClassFactory();
		}
		return _instance;
	}
	void ClassFactory::RegisterConstructor(String type, ConstructFunction function)
	{
		_constructors[type] = function;
		LogD << "Registering class: " << type;
	}
}