#include "FileDialog.h"

#include <windows.h>
#include <commdlg.h>
#include <iostream>
#include <fstream>

#include <locale>
#include <codecvt>
#include <string>




namespace simstudio {

	std::wstring ConvertToWstring(const String& data) {
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.from_bytes(data);

	}

	WString ConvertLPSTRToWString(LPSTR lpstr)
	{
		if (lpstr == NULL)
		{
			return std::wstring();
		}

		// Get the length of the input string
		int len = MultiByteToWideChar(CP_ACP, 0, lpstr, -1, NULL, 0);
		if (len == 0)
		{
			return std::wstring();
		}
		std::wstring wstr(len, 0);

		MultiByteToWideChar(CP_ACP, 0, lpstr, -1, &wstr[0], len);
		// Remove the null-terminator added by MultiByteToWideChar
		wstr.resize(len - 1);
		return wstr;
	}

	WString StringToWString(const String& str)
	{
		// Calculate the size needed for the wide string buffer
		size_t size_needed = mbstowcs(NULL, str.c_str(), 0) + 1;

		// Create a wide string buffer
		std::wstring wstr(size_needed, L'\0');

		// Convert the string
		mbstowcs(&wstr[0], str.c_str(), size_needed);

		// Remove the null terminator character from the string
		wstr.resize(size_needed - 1);

		return wstr;
	}



	void FileDialog::SaveJsonFile(const String& jsonData, const String& forcedExtension)
	{
		// Buffer to store the file name
		char szFile[260] = { 0 };

		// Initialize OPENFILENAME
		OPENFILENAME ofn;
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL; // No owner window
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = "JSON files\0*.json\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;


		char currentDir[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, currentDir);

		// Display the Save As dialog box 
		if (GetSaveFileName(&ofn) == TRUE)
		{

			LogE << ofn.lpstrFile;


			const auto filePath = ConvertLPSTRToWString(ofn.lpstrFile);


			std::ofstream outfile(filePath + ConvertToWstring(forcedExtension));
			if (outfile.is_open())
			{

				outfile << jsonData;
				outfile.close();
				LogI << "File saved to: " << ofn.lpstrFile;
			}
			else
			{
				LogE << "Failed to open the file.";
			}
		}
		else
		{
			LogE << "Save file dialog was canceled or an error occurred.";
		}

		SetCurrentDirectory(currentDir);
	}
	String FileDialog::ReadFileString(const String& forcedExtension)
	{
		OPENFILENAME ofn;       // common dialog box structure
		char szFile[1024] = { 0 };       // buffer for file name
		HWND hwnd = nullptr;    // owner window (nullptr if there isn't one)
		HANDLE hf;              // file handle

		// Initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = hwnd;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = forcedExtension.c_str();
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = nullptr;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = nullptr;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		// Display the Open dialog box.
		if (GetOpenFileName(&ofn) == TRUE)
		{
			std::ifstream file(ofn.lpstrFile);
			if (file.is_open())
			{
				std::stringstream buffer;
				buffer << file.rdbuf();
				return buffer.str();
			}
		}

		return String(); // Return an empty string if no file was selected or if an error occurred
	}
}