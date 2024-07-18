#include <iostream>

#include "src/prelude.h"

#include "src/app/prelude.h"
#include "src/utils/prelude.h"
#include "src/runs/run_xml.h"


#include "src/factory_registration.h"


using namespace simstudio;



int main() {


	RegisterClasses_OriginalName();

	App app;
	//run_directx(app);
	//run_xml(app);
	run_wasm_string_xml(app);

	return 0;
}
