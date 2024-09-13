#pragma once

#include "SimCore/Prelude.h"



namespace simstudio {

    class WasmExamples {

    public:

        static String Xml1() {
            std::string xml_content =
                "<app>\n"
                "    <name>Example app</name>\n"
                "\n"
                "    <simparams simtime=\"10:00\" />\n"
                "\n"
                "    <entities>\n"
                "        <source name=\"Source_1\" uid=\"Source_1\" spawn_time=\"uniform(5, 15)\" />\n"
                "        <station name=\"Station_0\" uid=\"Station_0\" operation_time=\"uniform(5, 12)\" />\n"
                "        <station name=\"Station_1\" uid=\"Station_1\" operation_time=\"uniform(5, 13)\" />\n"
                "        <station name=\"Station_2\" uid=\"Station_2\" operation_time=\"uniform(5, 14)\" />\n"
                "        <station name=\"Station_3\" uid=\"Station_3\" operation_time=\"uniform(5, 11)\" />\n"
                "        <station name=\"Station_4\" uid=\"Station_4\" operation_time=\"uniform(10, 15)\" />\n"
                "        <drain name=\"Drain_1\" uid=\"Drain_1\" />\n"
                "    </entities>\n"
                "\n"
                "    <connections>\n"
                "        <single a=\"Source_1\" b=\"Station_0\" />\n"
                "        <single a=\"Station_0\" b=\"Station_1\" />\n"
                "        <single a=\"Station_1\" b=\"Station_2\" />\n"
                "        <single a=\"Station_2\" b=\"Station_3\" />\n"
                "        <single a=\"Station_3\" b=\"Station_4\" />\n"
                "        <single a=\"Station_4\" b=\"Drain_1\" />\n"
                "    </connections>\n"
                "</app>\n";
            return xml_content;
        };



    };

};