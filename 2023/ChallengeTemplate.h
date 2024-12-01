#pragma once

#include "ChallengeBase.h"

class ChallengeTemplate : public ChallengeBase {

protected:
	bool HasInputFile() { return true; }
	std::string GetInputFile() { return "Test.txt"; }

	void Init();
	std::string RunChallengePart1(std::string input);
	std::string RunChallengePart2(std::string input);
};