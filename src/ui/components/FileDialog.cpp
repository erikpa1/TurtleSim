#include "FileDialog.h"

#include <windows.h>
#include <commdlg.h>
#include <iostream>
#include <fstream>




namespace simstudio {

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


			std::ofstream outfile(filePath);
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
}