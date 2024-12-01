#pragma once

#include "ChallengeBase.h"

class Challenge1 : public ChallengeBase {

protected:
	bool HasInputFile() { return true; }
	std::string GetInputFile() { return "Challenge1.txt"; }

	void Init();
	std::string RunChallengePart1(std::string input);
	std::string RunChallengePart2(std::string input);

private:
	bool CheckMatch(std::string line, int& value);
};