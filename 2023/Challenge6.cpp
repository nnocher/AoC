#include "Challenge6.h"

#include <math.h>
#include <vector>
#include "StringHelper.h"

void Challenge6::Init() {

}

std::string Challenge6::RunChallengePart1(std::string input) {
	std::vector<std::string> lines;
	StrSplit(input, "\n", lines);

	std::vector<std::string> times;
	std::vector<std::string> distances;

	StrSplit(lines.at(0), " ", times, false);
	StrSplit(lines.at(1), " ", distances, false);

	int total = 1;
	// loop through vector skipping first entry
	for (int i = 1; i < times.size(); i++) {
		total *= this->GetPossibleWins(std::stod(times.at(i)), std::stod(distances.at(i)));
	}

	return std::to_string(total);
}

std::string Challenge6::RunChallengePart2(std::string input) {
	std::vector<std::string> lines;
	StrSplit(input, "\n", lines);

	std::vector<std::string> times;
	std::vector<std::string> distances;

	StrSplit(lines.at(0), ":", times, false);
	StrSplit(lines.at(1), ":", distances, false);

	double time = std::stod(StrRemoveWhitespace(times.at(1)));
	double distance = std::stod(StrRemoveWhitespace(distances.at(1)));
	int total = this->GetPossibleWins(time, distance);

	return std::to_string(total);
}

int Challenge6::GetPossibleWins(double totalTime, double distance) {
	double runPressTime = this->EstimatePress(totalTime, distance);

	double nextWinningRun = ceil(runPressTime + 0.0001);
	double lastWinningRun = floor(totalTime - (runPressTime + 0.0001));

	return lastWinningRun - nextWinningRun + 1;
}

double Challenge6::EstimatePress(double totalTime, double distance) {
	
	// Estimate distance solved for p => p = 0.5 (sqrt (t^2 - 4d)
	return 0.5 * (totalTime - sqrt((totalTime * totalTime) - 4 * distance));
}

double Challenge6::EstiamteDistance(double pressTime, double totalTime) {

	// d = p * (t - p)
	return pressTime * (totalTime - pressTime);
}