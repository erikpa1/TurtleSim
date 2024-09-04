#include <iostream>

#include "SimCore/Prelude.h"

#include "src/app/world.h"
#include "src/app/prelude.h"
#include "src/utils/prelude.h"
#include "src/runs/run_xml.h"


#include "src/factory_registration.h"

#include "src/serialization/safejson.h"


using namespace simstudio;

#if IS_WINDOWS_PLATFORM

#include "run_sdl.h"
#endif



int main() {
	RegisterClasses();


#if IS_WINDOWS_PLATFORM

	run_sdl();
#endif
	//run_xml(app);
	//run_wasm_string_xml(app);

	return 0;
}
