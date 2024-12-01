#pragma once

#include "ChallengeBase.h"

struct Gear {
	int x;
	int y;

	int number1;
	int number2;

	Gear(int x, int y) : x(x), y(y), number1(0), number2(0) {}

	long long GetRatio() const {
		return number1 * number2;
	}
};

class Challenge3 : public ChallengeBase {

protected:
	bool HasInputFile() { return true; }
	std::string GetInputFile() { return "Challenge3.txt"; }

	void Init();
	std::string RunChallengePart1(std::string input);
	std::string RunChallengePart2(std::string input);

private:
	bool CheckSymbol(char c);
	void GetRatio(std::string line, int rangeStart, int rangeEnd, long long& r_ratio, bool& r_hasBoth);

	bool FindNumber(std::string line, int pos, int& number);
};