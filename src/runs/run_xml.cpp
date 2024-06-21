#include "run_xml.h"


#include "../external/tinyxml2.h"

#include "../utils/exe_dir.h"
#include "../serialization/safexml.h"



#include "../utils/prelude.h"
#include "../app/prelude.h"


using namespace tinyxml2;


namespace simstudio {
	void run_xml()
	{

		App app;


		String example_file = F("{}\\{}", GetSolutionDirectory(), "example.xml");

		SafeXml doc;
		doc.LoadFile(example_file);

		if (doc.ErrorID() == 0) {

			auto node_app = doc._document->FirstChildElement("app");


			if (node_app) {
				auto entities = node_app->FirstChildElement("entities");


				if (entities) {

					for (auto child = entities->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {

						auto child_type = child->Name();

						auto child_name = child->Attribute("name");
						auto child_uid = child->Attribute("uid");


						if (child_type == "source") {

						}
						else if (child_type == "station") {
							auto tmp = Share<Station>();
							tmp->_name = child_name;
							tmp->_uid = child_name;
							tmp->_any_operation_time._strValue = "uniform(5, 10)";
							app.AddEntity(tmp);
						}
						else if (child_type == "drain") {

						}
					}

				}
				else {
					LogE << "Entities was invalid";
				}

			}


			//XMLElement* titleElement = doc.FirstChildElement("app")->FirstChildElement("name");
			//auto title = titleElement->GetText();
			//LogI << "Name: " << title;
		}
		else {
			LogE << "Failed to open XML";
		}

		LogI << doc.ErrorID();




	}
}
