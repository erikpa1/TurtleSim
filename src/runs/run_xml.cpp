#include "run_xml.h"


#include "../utils/exe_dir.h"
#include "../utils/prelude.h"
#include "../app/prelude.h"
#include "../statistics/app_report_collector.h"



namespace simstudio {
	void run_xml(App& app)
	{

		String example_file = F("{}\\{}", GetSolutionDirectory(), "xml_examples\\example.xml");
		String example_file_1 = F("{}\\{}", GetSolutionDirectory(), "xml_examples\\example_1.xml");
		String example_file_2 = F("{}\\{}", GetSolutionDirectory(), "xml_examples\\example_2_conveyor.xml");
		String example_file_3 = F("{}\\{}", GetSolutionDirectory(), "xml_examples\\example_3_agv.xml");

		app.LoadFromXmlFile(example_file_3);
		app.Init();
		app.StartSimulation();

		SaveStatisticsRecord(app);

	}
}
