
#include "simpleson/json.h"
#include "nlohmann/json.hpp"

#include "../prelude.h"



namespace simstudio {

	class SafeJson {

	public:
		bool optimizeSpace = true;


	public:

		//Loading
		void ParseString(const String& str);


		template<typename T>
		T GetValue(const String& key, T notFound) {
			if (this->_internal.has_key(key)) {
				return (T)this->_internal[key];
			}
			else {

			}
		}

		String GetString(const String& key, const String& notFound);
		int GetInt(const String& key, int notFound);
		long GetLong(const String& key, long notFound);
		double GetDouble(const String& key, double notFound);


	public:
		//Writing


		void WriteString(const String& key, const String& value);
		void WriteFloat(const String& key, float value);
		void WriteDouble(const String& key, double value);
		void WriteInt(const String& key, int value);
		void WriteLong(const String& key, long value);
		void WriteBoolean(const String& key, bool value);


		String Dump();


	private:

		json::jobject _internal;
		nlohmann::json _internal1;
	};

}