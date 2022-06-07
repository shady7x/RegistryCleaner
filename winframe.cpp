#include "winframe.h" 
#include <iostream>

std::string winframe::rot13(std::wstring text_to_decode)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::string text = converter.to_bytes(text_to_decode);
	std::string final_result;
	for (std::string::iterator it = text.begin(); it != text.end(); ++it)
	{
		if (isalpha(*it))
		{
			bool is_lowcase = islower(*it);
			final_result.push_back((is_lowcase == true ? 97 : 65) + (*it - (is_lowcase == true ? 97 : 65) + 13) % 26);
		}
		else
		{
			final_result.push_back(*it);
		}
	}
	std::cout << std::endl;
	return final_result;
}

bool winframe::file_exists(const std::string &app_path) {
	std::ifstream fs(app_path.c_str());
	return fs.good();
}

void winframe::cast_to_upper(std::string &app_name)
{
	for (int i = 0; i < (int)app_name.size(); ++i)
	{
		if (islower(app_name[i]))
		{
			app_name[i] = toupper(app_name[i]);
		}
	}
}

void winframe::get_exe_name(std::string &app_path, std::string &app_name)
{
	bool fldot = false;
	TCHAR full_path[MAX_PATH];
	for (int i = 0; i < (int)app_path.size(); ++i)
		if (app_path[i] == '.')
			fldot = true;
	if (!fldot)
		app_path += ".exe";
	app_name = app_path;
	GetFullPathNameA(app_path.c_str(), MAX_PATH, full_path, NULL);
	app_path = full_path;
}

bool winframe::enable_extra_rights()
{
	HANDLE TokenHandle = { 0 };
	TOKEN_PRIVILEGES TokenPriv = { 0 };
	LUID lValueId = { 0 };
	if (!OpenProcessToken(GetCurrentProcess(), 0x28, &TokenHandle))
		return false;
	if (!LookupPrivilegeValue(0, SE_DEBUG_NAME, &lValueId))
		return false;
	TokenPriv.PrivilegeCount = 1;
	TokenPriv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	TokenPriv.Privileges[0].Luid = lValueId;
	if (AdjustTokenPrivileges(TokenHandle, 0, &TokenPriv, sizeof(TokenPriv), 0, 0))
		return true;
	return false;
}