#include "run_xml.h"


#include "../utils/exe_dir.h"
#include "../utils/prelude.h"
#include "../app/prelude.h"




namespace simstudio {
	void run_xml(App& app)
	{

		String example_file = F("{}\\{}", GetSolutionDirectory(), "xml_examples\\example.xml");
		String example_file_1 = F("{}\\{}", GetSolutionDirectory(), "xml_examples\\example_1.xml");

		app.LoadFromXmlFile(example_file_1);
		app.Init();
		app.StartSimulation();
		app.PrintFinalStatistics();

	}
}
