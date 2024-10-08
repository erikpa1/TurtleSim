

#include "safejson.h"



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
		try {
			_internal1 = nlohmann::json::parse(str);
		}
		catch (const std::exception& exc4)
		{
			LogE << exc4.what();
		}

	}

	String SafeJson::GetString(const String& key, const String& notFound)
	{
		_internal1.contains(key);
		if (_internal1.contains(key)) {
			return (String)_internal1[key];
		}
		else {
			return notFound;
		}
	}

	int SafeJson::GetInt(const String& key, int notFound)
	{
		if (_internal1.contains(key)) {
			return (int)_internal1[key];
		}
		else {
			return notFound;
		}
	}

	long SafeJson::GetLong(const String& key, long notFound)
	{
		if (_internal1.contains(key)) {
			return (int)_internal1[key];
		}
		else {
			return notFound;
		}
	}

	double SafeJson::GetDouble(const String& key, double notFound)
	{
		//TODO prepisat tieto duplicity do makra
		if (_internal1.contains(key)) {
			return (int)_internal1[key];
		}
		else {
			return notFound;
		}
	}

	Array<Shared<SafeJson>> SafeJson::GetObjectArray(const String& key)
	{
		if (_internal1.contains(key) && _internal1[key].is_array()) {

			Array<Shared<SafeJson>> result;

			nlohmann::json dataArray = _internal1[key];

			for (const auto& item : dataArray) {
				auto tmp = Share<SafeJson>();
				tmp->FromNlohmann(item);
				result.push_back(tmp);
			}

			return result;
		}
		else {
			return {};
		}
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
		return _internal1.dump(4, ' ', true);
	}

	void SafeJson::FromNlohmann(nlohmann::json obj)
	{
		_internal1 = obj;
	}



}