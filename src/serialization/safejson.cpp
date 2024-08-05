
#include "json.h"
#include "safejson.h"

using namespace json;


namespace simstudio {


	void SafeJson::ParseString(const String& str)
	{
		_internal = json::jobject::parse(str);
	}

	String SafeJson::GetString(const String& key, const String& notFound)
	{
		if (_internal.has_key(key)) {
			return (String)_internal[key];
		}
		else {
			return notFound;
		}
	}

	int SafeJson::GetInt(const String& key, int notFound)
	{
		if (_internal.has_key(key)) {
			return (int)_internal[key];
		}
		else {
			return notFound;
		}
	}

	long SafeJson::GetLong(const String& key, long notFound)
	{
		return 0;
	}

	double SafeJson::GetDouble(const String& key, double notFound)
	{
		return 0;
	}



}