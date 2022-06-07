#pragma once

#include <windows.h>
#include <string>
#include <fstream>
#include <filesystem>
#include "clean.h"

#define DEFX 196

namespace winframe 
{
	std::string rot13(std::wstring text_to_decode);
	bool file_exists(const std::string &app_path);
	void cast_to_upper(std::string &app_name);
	void get_exe_name(std::string &app_path, std::string &app_name);
	bool enable_extra_rights();
}