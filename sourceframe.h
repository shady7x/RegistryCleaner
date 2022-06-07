#pragma once

#include "winframe.h"

namespace sourceframe
{
	void clean_prefetch(std::string app_name_original, CClean &clean_cur);
	void clean_userassist(std::string value, CClean &clean_cur);
	void clean_store(std::string value, CClean &clean_cur);
}