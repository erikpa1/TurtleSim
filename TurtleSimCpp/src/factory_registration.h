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
		factory->RegisterClass<Agv>();
		factory->RegisterClass<SingleLane>();
		factory->RegisterClass<Loader>();
		factory->RegisterClass<Unloader>();
		factory->RegisterClass<Warehouse>();

		LogI << &factory;

	}

}