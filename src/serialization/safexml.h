#pragma once

#include "../prelude.h"

namespace tinyxml2 {
	class XMLDocument;
	class XMLElement;
}

namespace simstudio {


	class SafeXmlNode {

	public:
		tinyxml2::XMLElement* _element;

	public:

		SafeXmlNode(Shared<tinyxml2::XMLElement> &element);

		bool BoolVal();

	};


	class SafeXml {

	public:
		Shared< tinyxml2::XMLDocument> _document;

	public:


		void LoadFile(const String& path);
		int ErrorID();









	};



}