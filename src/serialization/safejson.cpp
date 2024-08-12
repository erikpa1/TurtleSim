
#include "json.h"
#include "safejson.h"

using namespace json;

#define WRITE_WITH_CONDITION(key, value, condition) \
    if (this->optimizeSpace) {                      \
        if (condition) {                            \
            this->_internal1[key] = value;          \
        }                                           \
    } else {                                        \
        this->_internal1[key] = value;              \
    }


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

	void SafeJson::WriteString(const String& key, const String& value)
	{
		WRITE_WITH_CONDITION(key, value, value != "")
	}

	void SafeJson::WriteFloat(const String& key, float value)
	{
		WRITE_WITH_CONDITION(key, value, value != 0.0)
	}

	void SafeJson::WriteFloat3(const String& key, float x, float y, float z)
	{
		float array[3] = { x, y, z };
		this->_internal1[key] = array;
	}

	void SafeJson::WriteDouble(const String& key, double value)
	{
		WRITE_WITH_CONDITION(key, value, value != 0)
	}

	void SafeJson::WriteDouble3(const String& key, double x, double y, double z)
	{
		double array[3] = { x, y, z };
		this->_internal1[key] = array;
	}

	void SafeJson::WriteInt(const String& key, int value)
	{
		WRITE_WITH_CONDITION(key, value, value != 0)
	}

	void SafeJson::WriteLong(const String& key, long value)
	{
		WRITE_WITH_CONDITION(key, value, value != 0)
	}

	void SafeJson::WriteBoolean(const String& key, bool value)
	{
		WRITE_WITH_CONDITION(key, value, value != false)
	}

	void SafeJson::WriteJson(const String& key, const SafeJson& another)
	{
		this->_internal1[key] = another._internal1;
	}

	void SafeJson::WriteJsonArray(const String& key, const Array<Shared<SafeJson>>& another)
	{
		if (this->optimizeSpace && another.size() == 0) {
			return;
		}

		Array<nlohmann::json> objects;
		objects.reserve(another.size());

		for (const auto& other : another) {
			objects.push_back(other->_internal1);
		}

		this->_internal1[key] = objects;
	}

	int SafeJson::GetKeysLength()
	{
		return this->_internal1.size();
	}

	String SafeJson::Dump()
	{
		return _internal1.dump(4, 4, true);
	}



}