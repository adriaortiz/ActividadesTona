#pragma once
//#include "Utilities.h"
#include "..\inc\Utilities.h"

namespace  Ranking
{
	const std::string pathRanking = "ranking.txt";

	std::map<std::string, int> get();

	void set(std::map<std::string, int> &rank);

	bool nameExist(std::string &name, std::map<std::string, int> &rank);

	void print(const std::map<std::string, int> &currentRank);

	void resetScore(std::map<std::string, int> &currentRank);
}
