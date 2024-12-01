#pragma once

#include "ChallengeBase.h"

#include <vector>

struct Galaxy {
	int x;
	int y;

	Galaxy(int x, int y) : x(x), y(y) {}
};

class Challenge11 : public ChallengeBase {
	std::vector<Galaxy> _galaxies;

protected:
	bool HasInputFile() { return true; }
	std::string GetInputFile() { return "Challenge11.txt"; }

	void Init();
	std::string RunChallengePart1(std::string input);
	std::string RunChallengePart2(std::string input);

private:
	void ExpandMap(std::vector<std::string>& rMap, int factor = 2);
	void FindGalaxies(std::vector<std::string>& rMap);
};