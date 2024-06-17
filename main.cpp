#include <iostream>

#include "src/prelude.h"

#include "src/app/prelude.h"
#include "src/utils/prelude.h"

//#include "src/external/tinyxml2.h"



using namespace simstudio;
//using namespace tinyxml2;

int main()
{

	//static const char* xml = "<element/>";
	//XMLDocument doc;
	//doc.Parse(xml);

	App app;
	Stepper steper;

	auto source = Share<Source>();
	source->_uid = "Source_1";
	source->_name = source->_uid;

	auto drain = Share<Drain>();
	drain->_uid = "Drain_1";
	drain->_name = drain->_uid;

	app.AddEntity(source);
	app.AddEntity(drain);

	for (int i = 0; i < 5; i++)
	{
		auto station = Share<Station>();
		station->_name = F("Station_{}", i);
		station->_uid = F("Station_{}", i);
		station->_any_operation_time._strValue = "uniform(5, 10)";
		app.AddEntity(station);
	}

	app.AddEntityConnection("Source_1", "Station_0");
	app.AddEntityConnection("Station_0", "Station_1");
	app.AddEntityConnection("Station_1", "Station_2");
	app.AddEntityConnection("Station_2", "Station_3");
	app.AddEntityConnection("Station_3", "Station_4");
	app.AddEntityConnection("Station_4", "Drain_1");

	app.Init();

	for (int i = 0; i < 20; i++)
	{
		app.Step(steper);
		steper.Step();
	}



	app.PrintFinalStatistics();

	//TODO zobrazit to XML v korytnacke

	return 0;
}
