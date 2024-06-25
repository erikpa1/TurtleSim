#include "run_xml.h"


#include "../utils/exe_dir.h"
#include "../utils/prelude.h"
#include "../app/prelude.h"




namespace simstudio {
	void run_xml(App& app)
	{
		String example_file = F("{}\\{}", GetSolutionDirectory(), "example.xml");
		app.LoadFromXmlFile(example_file);
		app.Init();
		app.StartSimulation();
		app.PrintFinalStatistics();

	}
}
