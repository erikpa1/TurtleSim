#include "run_xml.h"


#include "../utils/exe_dir.h"
#include "../utils/prelude.h"
#include "../app/prelude.h"
#include "../statistics/app_report_collector.h"


#include "wasm_test.h"


namespace simstudio {

	void run_xml(App& app)
	{

		String example_file = F("{}\\{}", GetSolutionDirectory(), "xml_examples\\example.xml");
		String example_file_1 = F("{}\\{}", GetSolutionDirectory(), "xml_examples\\example_1_paralel.xml");
		String example_file_2 = F("{}\\{}", GetSolutionDirectory(), "xml_examples\\example_2_conveyor.xml");
		String example_file_3 = F("{}\\{}", GetSolutionDirectory(), "xml_examples\\example_3_agv.xml");
		String example_file_4 = F("{}\\{}", GetSolutionDirectory(), "xml_examples\\example_4_warehouse.xml");

		app.LoadFromXmlFile(example_file_4);
		app.Init();
		app.StartSimulation();

		SaveStatisticsRecord(app);

	}

	void run_wasm_string_xml(App& app)
	{
		app.LoadFromXmlString(WasmExamples::Xml1());
		app.Init();
		app.StartSimulation();

		SaveStatisticsRecord(app);

	}





}
