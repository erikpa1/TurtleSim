#include "../../prelude.h"

namespace simstudio {


	class FileDialog {
	public:
		static void SaveJsonFile(const String& jsonData, const String& forcedExtension = ".json");
	};



}