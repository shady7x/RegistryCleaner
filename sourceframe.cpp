#include "sourceframe.h"
#include <iterator>
#include <iostream>

void sourceframe::clean_prefetch(std::string app_name, CClean &clean_cur)
{
	winframe::cast_to_upper(app_name);
	int cnt_all = 0, cnt_deleted = 0;
	std::string pattern = "";
	pattern.append("C:\\Windows\\Prefetch\\*");
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			bool found_entry = true;
			for (int i = 0; i < (int)app_name.size(); ++i)
			{
				if (app_name[i] != data.cFileName[i])
				{
					found_entry = false;
					break;
				}
			}
			if (found_entry)
			{
				++cnt_all;
				std::string address = data.cFileName;
				address = "C:\\Windows\\Prefetch\\" + address;
				std::cout << address.c_str() << std::endl;
				if (!std::remove(address.c_str()))
				{
					++cnt_deleted;
				}
				else
				{
					std::cout << "error deleting prefetch entry!" << std::endl;
				}
			}
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}
	if (cnt_deleted > 0)
		std::cout << std::endl;
	std::cout << "[*** " << cnt_deleted << '/' << cnt_all << " prefetch entries were deleted ***]" << std::endl;
	clean_cur.prefetch = (cnt_deleted == cnt_all);
}

void sourceframe::clean_userassist(std::string value, CClean &clean_cur)
{
	HKEY hkey;
	int cnt_all = 0, cnt_deleted = 0;
	if (ERROR_SUCCESS == RegOpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\UserAssist\\{CEBFF5CD-ACE2-4F4F-9178-9926F41749EA}\\Count", &hkey))
	{
		std::cout << "scanning registry section #1" << std::endl;
		LSTATUS delete_status = RegDeleteValue(hkey, value.c_str());
		while (RegDeleteValue(hkey, value.c_str()) == ERROR_SUCCESS);
		if (delete_status == 2)
		{
			
		}
		else
		{
			if (delete_status == ERROR_SUCCESS)
			{
				++cnt_deleted;
				std::cout << value << std::endl;
			}
			++cnt_all;
		}
		if (ERROR_SUCCESS == RegCloseKey(hkey))
		{
			std::cout << "finished scanning section" << std::endl;
			if (cnt_deleted > 0)
				std::cout << std::endl;
			std::cout << "[*** " << cnt_deleted << '/' << cnt_all << " user subkeys.values were deleted ***]" << std::endl;
			clean_cur.registryUser = (cnt_deleted == cnt_all);
		}
	}
	else
	{
		std::cout << "failed to open section #1" << std::endl;
	}
}

void sourceframe::clean_store(std::string value, CClean &clean_cur) // "Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Compatibility Assistant\\Store"
{
	HKEY hkey;
	int cnt_all = 0, cnt_deleted = 0;
	if (ERROR_SUCCESS == RegOpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Compatibility Assistant\\Store", &hkey))
	{
		std::cout << "scanning registry section #2" << std::endl;
		LSTATUS delete_status = RegDeleteValue(hkey, value.c_str());
		if (delete_status == 2)
		{

		}
		else
		{
			if (delete_status == ERROR_SUCCESS)
			{
				++cnt_deleted;
				std::cout << value << std::endl;
			}
			++cnt_all;
		}
		if (ERROR_SUCCESS == RegCloseKey(hkey))
		{
			std::cout << "finished scanning section" << std::endl;
			if (cnt_deleted > 0)
				std::cout << std::endl;
			std::cout << "[*** " << cnt_deleted << '/' << cnt_all << " store subkeys.values were deleted ***]" << std::endl;
			clean_cur.registryStore = (cnt_deleted == cnt_all);
		}
	}
	else
	{
		std::cout << "failed to open section #2" << std::endl;
	}
}