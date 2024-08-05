
#include "simpleson/json.h"

#include "../prelude.h"



namespace simstudio {

	class SafeJson {

	public:

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







	private:

		json::jobject _internal;
	};

}