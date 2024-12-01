#include "Challenge4.h"

#include "StringHelper.h"

void Challenge4::Init() {

}

std::string Challenge4::RunChallengePart1(std::string input) {
	std::vector<std::string> lines;
	StrSplit(input, "\n", lines);

	int totalPoints = 0;

	for (auto line : lines) {
		int numbersStart = line.find(":");
		std::vector<std::string> numberStrings;
		StrSplit(line.substr(numbersStart + 1), "|", numberStrings);

		std::vector<int> winningNumbers;
		std::vector<int> numbers;
		this->SplitNumbers(numberStrings.at(0), winningNumbers);
		this->SplitNumbers(numberStrings.at(1), numbers);

		int points = this->CalculatePoints(winningNumbers, numbers);
		totalPoints += points;
	}

	return std::to_string(totalPoints);
}

std::string Challenge4::RunChallengePart2(std::string input) {
	std::vector<std::string> lines;
	StrSplit(input, "\n", lines);

	int* cardMultipliers = new int[lines.size()];
	std::fill_n(cardMultipliers, lines.size(), 1);


	for (int cardNum = 0; cardNum < lines.size(); cardNum++) {
		int numbersStart = lines.at(cardNum).find(":");
		std::vector<std::string> numberStrings;
		StrSplit(lines.at(cardNum).substr(numbersStart + 1), "|", numberStrings);

		std::vector<int> winningNumbers;
		std::vector<int> numbers;
		this->SplitNumbers(numberStrings.at(0), winningNumbers);
		this->SplitNumbers(numberStrings.at(1), numbers);

		int points = this->CountWinners(winningNumbers, numbers);

		// Add multipliers
		int currentMultiplier = cardMultipliers[cardNum];
		for (int winCard = 1; winCard <= points; winCard++) {
			cardMultipliers[winCard + cardNum] += currentMultiplier;
		}
	}

	int totalCards = 0;
	for (int i = 0; i < lines.size(); i++) {
		totalCards += cardMultipliers[i];
	}

	return std::to_string(totalCards);
}

void Challenge4::SplitNumbers(std::string line, std::vector<int>& rResult) {
	std::vector<std::string> numberStrings;
	StrSplit(line, " ", numberStrings, false);

	for (auto str : numberStrings) {
		rResult.push_back(std::stoi(str));
	}
}

int Challenge4::CountWinners(std::vector<int>& rWinningNumbers, std::vector<int>& rNumbers) {
	int total = 0;

	for (auto n : rNumbers) {
		for (auto win : rWinningNumbers) {
			if (n == win) {
				total++;
				break;
			}
		}
	}

	return total;
}

int Challenge4::CalculatePoints(std::vector<int>& rWinningNumbers, std::vector<int>& rNumbers) {
	int total = 0;

	for (auto n : rNumbers) {
		for (auto win : rWinningNumbers) {
			if (n == win) {
				if (total == 0) {
					total = 1;
				}
				else {
					total *= 2;
				}
				break;
			}
		}
	}

	return total;
}