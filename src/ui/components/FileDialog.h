#include "../../prelude.h"

namespace simstudio {


	class FileDialog {
	public:
		static void SaveJsonFile(const String& jsonData, const String& forcedExtension = ".json");
		static String ReadFileString(const String& forcedExtension = ".json");
	
		static String GetJsonExtension() {
			return "JSON files\0*.json\0";
		}
	};



}