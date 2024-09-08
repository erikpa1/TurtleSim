#include "run_xml.h"


#include "../utils/exe_dir.h"
#include "../utils/prelude.h"
#include "../app/prelude.h"
#include "../statistics/app_report_collector.h"


#include "wasm_test.h"


namespace simstudio {

	void run_xml()
	{
		World world;

		String example_file = F("{}\\{}", GetSolutionDirectory(), "xml_examples\\example.xml");
		String example_file_1 = F("{}\\{}", GetSolutionDirectory(), "xml_examples\\example_1_paralel.xml");
		String example_file_2 = F("{}\\{}", GetSolutionDirectory(), "xml_examples\\example_2_conveyor.xml");
		String example_file_3 = F("{}\\{}", GetSolutionDirectory(), "xml_examples\\example_3_agv.xml");
		String example_file_4 = F("{}\\{}", GetSolutionDirectory(), "xml_examples\\example_4_warehouse.xml");

		world.LoadFromXmlFile(example_file_4);
		world.Init();
		world.StartSimulation();

		SaveStatisticsRecord(world);

	}

	void run_wasm_string_xml()
	{
		World world;

		world.LoadFromXmlString(WasmExamples::Xml1());
		world.Init();
		world.StartSimulation();

		SaveStatisticsRecord(world);

	}





}
