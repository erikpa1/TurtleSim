#pragma once

#include "SimCore/Prelude.h"

namespace tinyxml2 {
	class XMLDocument;
	class XMLElement;
}

namespace simstudio {



	class SafeXmlNode {

	public:
		tinyxml2::XMLElement* _element;

	public:

		SafeXmlNode(tinyxml2::XMLElement* element);

		int GetIntAttrib(const String& key, int notFoud = 0);
		double GetDoubleAttrib(const String& key, double notFoud = 0);
		bool GetBoolAttrib(const String& key, bool notFoud = false);
		String GetStringAttrib(const String& key, String notFound = "");

	};


	class SafeXml {

	public:
		Shared< tinyxml2::XMLDocument> _document;

	public:


		void LoadFile(const String& path);
		void LoadString(const String& xmlString);
		int ErrorID();









	};



}