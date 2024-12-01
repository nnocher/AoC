#include "Challenge3.h"

#include "Globals.h"

void Challenge3::Init() {

}

std::string Challenge3::RunChallengePart1(std::string input) {
	int sum = 0;

	std::vector<std::string> lines;
	StrSplit(input, "\n", lines);

	for (int line = 0; line < lines.size(); line++) {
		std::string currentLine = lines.at(line);

		int numberStart = -1;
		int numberEnd = -1;

		for (int i = 0; i < currentLine.length(); i++) {
			char c = currentLine[i];

			if (c >= '0' && c <= '9') {
				if (numberStart < 0) {
					numberStart = i;
				}
				else if (i == currentLine.length() - 1) {
					// Line end = Number end
					numberEnd = i + 1;
				}
			}
			else if (numberStart >= 0) {
				// Number end
				numberEnd = i;
			}

			if (numberEnd > -1) {
				int number = std::stoi(SUBSTRING(currentLine, numberStart, numberEnd));

				int rangeStart = numberStart - 1;
				if (rangeStart < 0) {
					rangeStart = 0;
				}

				int rangeEnd = numberEnd + 1;
				if (rangeEnd > currentLine.length() - 1) {
					rangeEnd = currentLine.length() - 1;
				}

				bool hasSymbol = false;

				// Check for symbol
				// top
				if (line > 0) {
					std::string checkStr = SUBSTRING(lines.at(line - 1), rangeStart, rangeEnd);

					for (auto check : checkStr) {
						if (this->CheckSymbol(check)) {
							hasSymbol = true;
							break;
						}
					}
				}

				// current
				if (!hasSymbol) {
					std::string checkStr = SUBSTRING(currentLine, rangeStart, rangeEnd);

					if (this->CheckSymbol(checkStr[0]) || this->CheckSymbol(checkStr[checkStr.length() - 1])) {
						hasSymbol = true;
					}
				}

				// bottom
				if (!hasSymbol && line + 1 < currentLine.length()) {
					std::string checkStr = SUBSTRING(lines.at(line + 1), rangeStart, rangeEnd);

					for (auto check : checkStr) {
						if (this->CheckSymbol(check)) {
							hasSymbol = true;
							break;
						}
					}
				}

				if (hasSymbol) {
					sum += number;
				}

				numberStart = -1;
				numberEnd = -1;
			}
		}
	}
	
	return std::to_string(sum);
}

std::string Challenge3::RunChallengePart2(std::string input) {
	long long sum = 0;

	std::vector<std::string> lines;
	StrSplit(input, "\n", lines);

	std::vector<Gear> gears;

	for (int y = 0; y < lines.size(); y++) {
		int lastOffset = 0;

		do {
			int index = lines.at(y).find("*", lastOffset);

			if (index >= 0) {
				gears.push_back(Gear(index, y));
			}
			lastOffset = index + 1;
		} while (lastOffset > 0);
	}

	for (Gear& gear : gears) {
		int startX = gear.x - 1;
		if (startX < 0) {
			startX = 0;
		}
		int startY = gear.y - 1;
		if (startY < 0) {
			startY = 0;
		}

		for (int y = startY; y < startY + 3 && y < lines.size(); y++) {
			bool checkForTwo = false;
			if (!IsNumeric(lines.at(y).at(startX + 1))) {
				// check for 2 numbers
				checkForTwo = true;
			}

			for (int x = startX; x < startX + 3 && x < lines.at(y).length(); x++) {
				int foundNumber = 0;
				if (this->FindNumber(lines.at(y), x, foundNumber)) {
					if (gear.number1 == 0) {
						gear.number1 = foundNumber;
					}
					else {
						gear.number2 = foundNumber;
					}

					if (!checkForTwo) {
						break;
					}
				}
			}
		}
	}

	int count = 0;
	for (Gear& gear : gears) {
		sum += gear.number1 * gear.number2;

		PrintLine("Gear " + std::to_string(count++) + " Number1: " + std::to_string(gear.number1) + " Number2: " + std::to_string(gear.number2) + " Ratio: " + std::to_string(gear.number1 * gear.number2) + " Sum: " + std::to_string(sum));
	}

	return std::to_string(sum);
}

bool Challenge3::FindNumber(std::string line, int pos, int& number) {
	if (!IsNumeric(line.at(pos))) {
		return false;
	}

	// check to the left
	int start = pos;
	while (start > 0 && IsNumeric(line.at(start - 1))) {
		start--;
	}

	// check to the right
	int length = 1;
	while (start + length < line.length() && IsNumeric(line.at(start + length))) {
		length++;
	}

	number = std::stoi(line.substr(start, length));
	return true;
}

//std::string Challenge3::RunChallengePart2(std::string input) {
//	long long sum = 0;
//
//	std::vector<std::string> lines;
//	StrSplit(input, "\n", lines);
//
//	for (int line = 0; line < lines.size(); line++) {
//		std::string currentLine = lines.at(line);
//
//		int currentStart = 0;
//		do {
//			int gearIndex = currentLine.find('*', currentStart);
//
//			bool hasBoth = false;
//			long long currentGearRatio = -1;
//
//			if (gearIndex == -1) {
//				break;
//			}
//
//			int rangeStart = gearIndex - 1;
//			if (rangeStart < 0) {
//				rangeStart = 0;
//			}
//
//			int rangeEnd = gearIndex + 1;
//			if (rangeEnd >= currentLine.length()) {
//				rangeEnd = currentLine.length() - 1;
//			}
//
//			// top
//			if (line > 0) {
//				this->GetRatio(lines.at(line - 1), rangeStart, rangeEnd, currentGearRatio, hasBoth);
//			}
//
//			// current
//			if (!hasBoth) {
//				this->GetRatio(currentLine, rangeStart, rangeEnd, currentGearRatio, hasBoth);
//			}
//
//			// bottom
//			if (!hasBoth && line + 1 < lines.size()) {
//				this->GetRatio(lines.at(line + 1), rangeStart, rangeEnd, currentGearRatio, hasBoth);
//			}
//
//			if (hasBoth) {
//				sum += currentGearRatio;
//			}
//
//			currentStart = gearIndex + 1;
//		} while (currentStart != 0);
//	}
//
//	return "Sum of part numbers: " + std::to_string(sum);
//}

bool Challenge3::CheckSymbol(char c) {
	return ((c < '0' || c > '9') && c != '.');
}

void Challenge3::GetRatio(std::string line, int rangeStart, int rangeEnd, long long& r_ratio, bool& r_hasBoth) {
	int checkStrLeft = rangeStart;
	int checkStrRight = rangeEnd;

	// Check left
	while (checkStrLeft != 0 && line[checkStrLeft] >= '0' && line[checkStrLeft] <= '9') {
		if (checkStrLeft > 0 && line[checkStrLeft - 1] >= '0' && line[checkStrLeft - 1] <= '9') {
			checkStrLeft--;
		}
		else {
			break;
		}
	}
	while (checkStrLeft < checkStrRight && (line[checkStrLeft] < '0' || line[checkStrLeft] > '9')) {
		checkStrLeft++;
	}

	// Check right
	while (checkStrRight != line.length() - 1 && line[checkStrRight] >= '0' && line[checkStrRight] <= '9') {
		if (checkStrLeft < line.length() - 1 && line[checkStrRight] >= '0' && line[checkStrRight] <= '9') {
			checkStrRight++;
		}
		else {
			break;
		}
	}
	while (checkStrRight > checkStrLeft && (line[checkStrRight - 1] < '0' || line[checkStrRight - 1] > '9')) {
		checkStrRight--;
	}

	std::string checkString = SUBSTRING(line, checkStrLeft, checkStrRight);

	if (checkString.length() > 0) {
		int splitIndex = -1;
		for (int cIndex = 0; cIndex < checkString.length(); cIndex++) {
			if (checkString[cIndex] < '0' || checkString[cIndex] > '9') {
				splitIndex = cIndex;
			}
		}

		if (splitIndex == -1) {
			if (r_ratio > 0) {
				r_hasBoth = true;
			}
			else {
				r_ratio = 1;
			}

			r_ratio *= std::stoll(checkString);
		}
		else {
			r_ratio = std::stoll(checkString.substr(0, splitIndex));
			r_ratio *= std::stoll(checkString.substr(splitIndex + 1));
			r_hasBoth = true;
		}
	}
}