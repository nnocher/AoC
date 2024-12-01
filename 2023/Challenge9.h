#pragma once

#include "ChallengeBase.h"

#include <vector>

class Challenge9 : public ChallengeBase {

protected:
	bool HasInputFile() { return true; }
	std::string GetInputFile() { return "Challenge9.txt"; }

	void Init();
	std::string RunChallengePart1(std::string input);
	std::string RunChallengePart2(std::string input);

private:
	void GetRuns(std::vector<std::vector<int>>& rRuns);
	int Extrapolate(std::vector<std::vector<int>>& rRuns);
	int ExtrapolateFront(std::vector<std::vector<int>>& rRuns);
};