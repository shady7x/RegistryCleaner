#include <iostream>
#include "sourceframe.h"

CClean clean_extern, clean_intern;

inline void skip_lines(int n)
{
	for (int i = 0; i <= n; ++i)
		std::cout << std::endl;
}

inline void new_block(int n)
{
	for (int i = 0; i < n; ++i)
		std::cout << char(DEFX);
	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	if (!winframe::enable_extra_rights())
	{
		std::cout << "launch as admin !" << std::endl;
		system("pause");
		return -7;
	}
	else
	{
		std::cout << "[rights enabled]" << std::endl;
	}
	std::cout << "1 - launch and clean afterwards  2 - clean" << std::endl << "-> ";
	short command;
	std::cin >> command;

	std::string u1 = argv[0];
	std::string u2 = u1.substr(0, u1.find_last_of("\\") + 1);
	std::string app_name_intern = u1.substr(u2.size(), (int)u1.size() - (int)u2.size());

	new_block(42);
	std::cout << "application's name: ";
	std::string app_path, app_name;
	std::cin >> app_path;
	std::cout << "current executable: " << app_name_intern << std::endl;

	winframe::get_exe_name(app_path, app_name);
	bool fixln = 0;
	if (command == 1)
	{
		if (winframe::file_exists(app_path))
		{
			system(app_path.c_str());
		}
		else
		{
			std::cout << std::endl << "[*** file not found, executing command 2 ***]";
			fixln = 1;
		}
	}

	/* extern */
	skip_lines(2 - fixln);
	std::cout << app_name << std::endl;
	new_block((int)app_name.size());
	sourceframe::clean_prefetch(app_name, clean_extern);
	skip_lines(0);
	std::wstring u2w(app_path.begin(), app_path.end());
	sourceframe::clean_userassist(winframe::rot13(u2w), clean_extern);
	sourceframe::clean_store(app_path, clean_extern);
	//skip_lines(3);
	/* intern */
	skip_lines(3);
	std::cout << app_name_intern << std::endl;
	new_block((int)app_name_intern.size());
	sourceframe::clean_prefetch(app_name_intern, clean_intern);
	skip_lines(0);
	std::wstring u1w(u1.begin(), u1.end());
	sourceframe::clean_userassist(winframe::rot13(u1w), clean_intern);
	sourceframe::clean_store(u1, clean_intern);

	skip_lines(2);

	new_block(40);

	if (clean_extern.successfully() && clean_intern.successfully())
		std::cout << ">>> everything cleaned successfully <<<";
	else
		std::cout << "<<<<<<<<< something went wrong >>>>>>>>>";

	std::cout << std::endl;

	new_block(40);

	skip_lines(2);
	system("pause");
	//RegDeleteKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Compatibility Assistant\\Store\\");
    return 0;
} 

  
/*

P:\Hfref\Byrt\fbhepr\ercbf\fbheprsenzr\Eryrnfr\fbheprsenzr.rkr
P:\Hfref\Byrt\fbhepr\ercbf\fbheprsenzr\Eryrnfr\1.rkr

*/