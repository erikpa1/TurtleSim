#include "exe_dir.h"


#include <string>
#include <iostream>
#include <filesystem>


#if IS_WINDOWS_PLATFORM
#include <windows.h>
#endif


String normalizePath(const std::string& path) {
	std::filesystem::path p(path);
	std::filesystem::path normalized = std::filesystem::canonical(p);
	return normalized.string();
}


String simstudio::GetExecutionDirectory()
{


#if IS_WINDOWS_PLATFORM
	char path[MAX_PATH];
	HMODULE hModule = GetModuleHandle(nullptr);
	if (GetModuleFileName(hModule, path, MAX_PATH) == 0) {
		// Handle error
		return "";
	}

	std::string fullPath(path);
	std::string::size_type pos = fullPath.find_last_of("\\/");
	return (std::string::npos == pos)
		? ""
		: fullPath.substr(0, pos);
#else
	return "";
#endif



}

String simstudio::GetSolutionDirectory()
{
#if IS_WINDOWS_PLATFORM
	return normalizePath(GetExecutionDirectory() + "\\..\\..\\..\\..\\");
#else
	return "";
#endif

}
