#pragma once
//#include "Utilities.h"
#include "..\inc\Utilities.h"
//#include "Ranking.h"
#include "..\inc\Ranking.h"

namespace Menus
{
	void score(int score, std::map<std::string, int> ranking);
	void mainMenu();
	void ranking();
	bool confirm();
}

