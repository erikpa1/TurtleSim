#include "safexml.h"


#include "../external/tinyxml2.h"

using namespace tinyxml2;

namespace simstudio {

	//Safe node code
	SafeXmlNode::SafeXmlNode(Shared<tinyxml2::XMLElement>& element)
	{
		//_element = element;
	}

	bool SafeXmlNode::BoolVal()
	{
		return false;
	}


	//Safe xml node
	void SafeXml::LoadFile(const String& path)
	{
		_document = Share<XMLDocument>();
		_document->LoadFile(path.c_str());

	}
	int SafeXml::ErrorID()
	{
		if (_document) {
			return _document->ErrorID();
		}
		else {
			return -1;
		}
	}
}