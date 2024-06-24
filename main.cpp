#include <iostream>

#include "src/prelude.h"

#include "src/app/prelude.h"
#include "src/utils/prelude.h"
#include "src/runs/run_xml.h"

#include "run_directx.h"

#include "src/factory_registration.h"


using namespace simstudio;



int main() {

	RegisterClasses();

	auto factory = ClassFactory::Instance();
	LogI << &factory;

	App app;

	run_directx(app);
	run_xml();


	return 0;
}