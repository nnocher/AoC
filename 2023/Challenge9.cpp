#include "Challenge9.h"

#include "StringHelper.h"

void Challenge9::Init() {

}

std::string Challenge9::RunChallengePart1(std::string input) {
	std::vector<std::string> lines;
	StrSplit(input, "\n", lines);

	int result = 0;
	for (std::string line : lines) {
		std::vector<std::string> numStrings;
		StrSplit(line, " ", numStrings);

		std::vector<int> numbers;
		for (std::string str : numStrings) {
			numbers.push_back(std::stoi(str));
		}

		std::vector<std::vector<int>> runs;
		runs.push_back(numbers);
		
		this->GetRuns(runs);
		result += this->Extrapolate(runs);
	}

	return std::to_string(result);
}

std::string Challenge9::RunChallengePart2(std::string input) {
	std::vector<std::string> lines;
	StrSplit(input, "\n", lines);

	int result = 0;
	for (std::string line : lines) {
		std::vector<std::string> numStrings;
		StrSplit(line, " ", numStrings);

		std::vector<int> numbers;
		for (std::string str : numStrings) {
			numbers.push_back(std::stoi(str));
		}

		std::vector<std::vector<int>> runs;
		runs.push_back(numbers);

		this->GetRuns(runs);
		result += this->ExtrapolateFront(runs);
	}

	return std::to_string(result);
}

void Challenge9::GetRuns(std::vector<std::vector<int>>& rRuns) {
	std::vector<int>* pPreviousRun = &*rRuns.begin();
	bool hasNonZero = true;
	while (hasNonZero) {
		std::vector<int> currentResult;
		hasNonZero = false;

		for (int i = 0; i + 1 < pPreviousRun->size(); i++) {
			int result = pPreviousRun->at(i + 1) - pPreviousRun->at(i);
			currentResult.push_back(result);

			if (result != 0) {
				hasNonZero = true;
			}
		}

		rRuns.push_back(currentResult);
		pPreviousRun = &rRuns.back();
	}
}

int Challenge9::Extrapolate(std::vector<std::vector<int>>& rRuns) {
	int lastValue = 0;
	for (int i = rRuns.size() - 1; i >= 0; i--) {
		lastValue += rRuns.at(i).back();
		rRuns.at(i).push_back(lastValue);
	}

	return rRuns.at(0).back();
}

int Challenge9::ExtrapolateFront(std::vector<std::vector<int>>& rRuns) {
	int lastValue = 0;
	for (int i = rRuns.size() - 1; i >= 0; i--) {
		lastValue = rRuns.at(i).front() - lastValue;
		rRuns.at(i).insert(rRuns.at(i).begin(), lastValue);
	}

	return rRuns.at(0).front();
}