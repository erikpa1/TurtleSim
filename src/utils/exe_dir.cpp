#include "exe_dir.h"

#include <windows.h>
#include <string>
#include <iostream>
#include <filesystem>


String normalizePath(const std::string& path) {
    std::filesystem::path p(path);
    std::filesystem::path normalized = std::filesystem::canonical(p);
    return normalized.string();
}


String simstudio::GetExecutionDirectory()
{
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
}

String simstudio::GetSolutionDirectory()
{
    return normalizePath(GetExecutionDirectory() + "\\..\\..\\..\\..\\");
}
