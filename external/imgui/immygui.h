

#include <string>

namespace ImGui
{
	void StringInput(const char* label, std::string& str);

	void CstrInput(const char* label, char* inputBuffer, size_t bufferSize);
	void FloatInput(const char* label, float* value);
	void IntInput(const char* label, int* value);
	void LongInput(const char* label, long* value);
}
