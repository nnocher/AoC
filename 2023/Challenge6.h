#pragma once

#include "ChallengeBase.h"

class Challenge6 : public ChallengeBase {

protected:
	bool HasInputFile() { return true; }
	std::string GetInputFile() { return "Challenge6.txt"; }

	void Init();
	std::string RunChallengePart1(std::string input);
	std::string RunChallengePart2(std::string input);

private:
	int GetPossibleWins(double totalTime, double distance);
	double EstimatePress(double totalTime, double distance);
	double EstiamteDistance(double pressTime, double totalTime);
};