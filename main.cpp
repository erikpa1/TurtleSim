#include <iostream>

#include "src/prelude.h"

#include "src/app/prelude.h"
#include "src/utils/prelude.h"
#include "src/runs/run_xml.h"


#include "src/factory_registration.h"


using namespace simstudio;

#if IS_WINDOWS_PLATFORM
#include "run_directx.h"
#endif



int main() {


	RegisterClasses();

	App app;

#if IS_WINDOWS_PLATFORM
	run_directx(app);
#endif
	//run_xml(app);
	//run_wasm_string_xml(app);

	return 0;
}
