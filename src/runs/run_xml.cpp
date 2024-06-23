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

		ClassFactory factory;
		factory.RegisterClass<Source>();
		factory.RegisterClass<Station>();
		factory.RegisterClass<Drain>();

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

						SafeXmlNode safe_child(child);

						auto child_name = safe_child.GetStringAttrib("name");
						auto child_uid = safe_child.GetStringAttrib("uid");


						auto entity = factory.Construct<Entity>(child_type);
						entity->FromXml(safe_child);
						app.AddEntity(entity);

					}
				}
				else {
					LogE << "Entities was invalid";
				}

				auto connections = node_app->FirstChildElement("connections");

				if (connections) {
					for (auto child = connections->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
						SafeXmlNode connection(child);

						auto a = connection.GetStringAttrib("a");
						auto b = connection.GetStringAttrib("b");

						if (a != "" && b != "") {
							app.AddEntityConnection(a, b);
						}
						else {
							LogE << "Incomplete connection, " << a << " " << b;
						}
					}

				}
				else {
					LogE << "Connections was invalid";
				}




			}
		}
		else {
			LogE << "Failed to open XML";
		}

		LogI << doc.ErrorID();

		app.Init();
		app.StartSimulation();
		app.PrintFinalStatistics();

	}
}
