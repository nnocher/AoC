#pragma once

#include "ChallengeBase.h"

#include <vector>

struct Cube {
	int count;
	std::string color;

public:
	Cube(int count, std::string color) : count(count), color(color) {};
};

class Challenge2 : public ChallengeBase {

	std::vector<Cube> _bag;

protected:
	bool HasInputFile() { return true; }
	std::string GetInputFile() { return "Challenge2.txt"; }

	void Init();
	std::string RunChallengePart1(std::string input);
	std::string RunChallengePart2(std::string input);

private:
	bool CheckBag(std::string color, int count);
};