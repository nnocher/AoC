#include "Challenge2.h"

#include "Globals.h"

void Challenge2::Init() {
	
}

std::string Challenge2::RunChallengePart1(std::string input) {
	// Init
	this->_bag.clear();
	this->_bag.push_back(Cube(12, "red"));
	this->_bag.push_back(Cube(13, "green"));
	this->_bag.push_back(Cube(14, "blue"));

	int idSum = 0;

	int currentIndex = 0;
	do {
		int lineEnd = input.find('\n', currentIndex);
		std::string currentLine = SUBSTRING(input, currentIndex, lineEnd);

		bool validGame = true;
		int idStart = currentLine.find(" ");
		int idEnd = currentLine.find(":");
		int id = std::stoi(SUBSTRING(currentLine, idStart, idEnd));

		int roundStart = idEnd + 2;
		do {
			int roundEnd = currentLine.find(";", roundStart);
			std::string round = SUBSTRING(currentLine, roundStart, roundEnd);

			int block = 0;
			do {
				int blockEnd = round.find(",", block);
				int separator = round.find(" ", block) + 1;
				int count = std::stoi(SUBSTRING(round, block, separator));
				std::string color = SUBSTRING(round, separator, blockEnd);

				validGame = this->CheckBag(color, count);

				block = blockEnd + 2;
			} while (block != 1 && validGame);

			roundStart = roundEnd + 2;
		} while (roundStart != 1 && validGame);

		if (validGame) {
			idSum += id;
		}

		currentIndex = lineEnd + 1;
	} while (currentIndex != 0);

	return std::to_string(idSum);
}

std::string Challenge2::RunChallengePart2(std::string input) {
	int total = 0;

	int currentIndex = 0;
	do {
		int lineEnd = input.find('\n', currentIndex);
		std::string currentLine = SUBSTRING(input, currentIndex, lineEnd);

		bool validGame = true;
		int idStart = currentLine.find(" ");
		int idEnd = currentLine.find(":");
		int id = std::stoi(SUBSTRING(currentLine, idStart, idEnd));

		int maxRed = 0;
		int maxGreen = 0;
		int maxBlue = 0;

		int roundStart = idEnd + 2;
		do {
			int roundEnd = currentLine.find(";", roundStart);
			std::string round = SUBSTRING(currentLine, roundStart, roundEnd);

			int block = 0;
			do {
				int blockEnd = round.find(",", block);
				int separator = round.find(" ", block) + 1;
				int count = std::stoi(SUBSTRING(round, block, separator));
				std::string color = SUBSTRING(round, separator, blockEnd);

				if (color == "red" && maxRed < count) {
					maxRed = count;
				}
				else if (color == "green" && maxGreen < count) {
					maxGreen = count;
				}
				else if (color == "blue" && maxBlue < count) {
					maxBlue = count;
				}

				block = blockEnd + 2;
			} while (block != 1 && validGame);

			roundStart = roundEnd + 2;
		} while (roundStart != 1 && validGame);

		total += maxRed * maxGreen * maxBlue;

		currentIndex = lineEnd + 1;
	} while (currentIndex != 0);

	return std::to_string(total);
}

bool Challenge2::CheckBag(std::string color, int count) {
	for (auto c : this->_bag) {
		if (c.color == color && c.count >= count) {
			return true;
		}
	}

	return false;
}