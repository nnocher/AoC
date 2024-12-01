#pragma once

#include "ChallengeBase.h"

#include <vector>

class Challenge4 : public ChallengeBase {

protected:
	bool HasInputFile() { return true; }
	std::string GetInputFile() { return "Challenge4.txt"; }

	void Init();
	std::string RunChallengePart1(std::string input);
	std::string RunChallengePart2(std::string input);

private:
	int CountWinners(std::vector<int>& rWinningNumbers, std::vector<int>& rNumbers);
	int CalculatePoints(std::vector<int>& rWinningNumbers, std::vector<int>& rNumbers);
	void SplitNumbers(std::string line, std::vector<int>& rResult);
};