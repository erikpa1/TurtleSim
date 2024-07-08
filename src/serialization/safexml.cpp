#include "safexml.h"


#include "../external/tinyxml2.h"

using namespace tinyxml2;

namespace simstudio {

	//Safe node code
	SafeXmlNode::SafeXmlNode(XMLElement* element)
	{
		_element = element;
	}

	int SafeXmlNode::GetIntAttrib(const String& key, int notFoud) {
		if (_element) {
			return _element->IntAttribute(key.c_str(), notFoud);
		}
		else {
			return notFoud;
		}
	}

	double SafeXmlNode::GetDoubleAttrib(const String& key, double notFoud) {
		if (_element) {
			return _element->DoubleAttribute(key.c_str(), notFoud);
		}
		else {
			return notFoud;
		}
	}


	bool SafeXmlNode::GetBoolAttrib(const String& key, bool notFoud)
	{
		if (_element) {
			return _element->BoolAttribute(key.c_str(), notFoud);
		}
		else {
			return notFoud;
		}
	}

	String SafeXmlNode::GetStringAttrib(const String& key, String notFoud)
	{
		if (_element) {
			auto value = _element->Attribute(key.c_str());

			if (value) {
				return value;
			}
			else {
				return notFoud;
			}

		}
		else {
			return notFoud;
		}
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