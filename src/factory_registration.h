#pragma once

#include "utils/prelude.h"
#include "serialization/prelude.h"
#include "app/prelude.h"



namespace simstudio {

	void RegisterClasses() {
		auto factory = ClassFactory::Instance();

		factory->RegisterClass<Source>();
		factory->RegisterClass<Station>();
		factory->RegisterClass<Drain>();
		factory->RegisterClass<Buffer>();
		factory->RegisterClass<Conveyor>();

		LogI << &factory;

	}

}