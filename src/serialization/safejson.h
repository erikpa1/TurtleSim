

#include "nlohmann/json.hpp"

#include "../prelude.h"



namespace simstudio {

	class SafeJson {

	public:
		bool optimizeSpace = true;


	public:

		//Loading
		void ParseString(const String& str);


		String GetString(const String& key, const String& notFound);
		int GetInt(const String& key, int notFound);
		long GetLong(const String& key, long notFound);
		double GetDouble(const String& key, double notFound);


	public:
		//Writing


		void WriteString(const String& key, const String& value);
		void WriteFloat(const String& key, float value);
		void WriteFloat3(const String& key, float x, float y, float z);
		void WriteDouble(const String& key, double value);
		void WriteDouble3(const String& key, double x, double y, double z);
		void WriteInt(const String& key, int value);
		void WriteLong(const String& key, long value);
		void WriteBoolean(const String& key, bool value);

		void WriteJson(const String& key, const SafeJson& another);
		void WriteJsonArray(const String& key, const Array<Shared<SafeJson>>& another);

		int GetKeysLength();




		String Dump();


	private:

		nlohmann::json _internal1;
	};

}