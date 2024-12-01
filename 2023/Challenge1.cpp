#include "Challenge1.h"

#include "Globals.h"

void Challenge1::Init() {

}

std::string Challenge1::RunChallengePart1(std::string input) {

	int sum = 0;

	int currentIndex = 0;
	do {
		int lineEnd = input.find('\n', currentIndex);
		std::string currentLine = SUBSTRING(input, currentIndex, lineEnd);

		int first = -1;
		int last = -1;

		for (auto c : currentLine) {
			if (c >= '0' && c <= '9') {
				// Is numeric
				if (first < 0) {
					first = c - 48;
				}
				else {
					last = c - 48;
				}
			}
		}

		if (last < 0) {
			last = first;
		}

		sum += first * 10 + last;

		currentIndex = lineEnd + 1;
	} while (currentIndex != 0);

	return std::to_string(sum);
}

std::string Challenge1::RunChallengePart2(std::string input) {
	int sum = 0;

	int currentIndex = 0;
	do {
		int lineEnd = input.find('\n', currentIndex);
		std::string currentLine = SUBSTRING(input, currentIndex, lineEnd);

		int length = currentLine.length();
		int first = -1;
		int last = -1;

		for (int i = 0; i < length; i++) {
			if ((first >= 0 || this->CheckMatch(currentLine.substr(i), first)) &
				(last >= 0 || this->CheckMatch(currentLine.substr((length - 1) - i), last))) {
				break;
			}
		}

		sum += first * 10 + last;

		currentIndex = lineEnd + 1;
	} while (currentIndex != 0);

	return std::to_string(sum);
}

bool Challenge1::CheckMatch(std::string line, int& value) {

	// Numeric check
	if (line[0] >= '0' && line[0] <= '9') {
		value = line[0] - 48;
		return true;
	}

	// shortcut exit
	if (line.length() < 3) {
		return false;
	}

	// Word lookup
	if (StrStartsWith(line, "one", false)) {
		value = 1;
		return true;
	}
	if (StrStartsWith(line, "two", false)) {
		value = 2;
		return true;
	}
	if (StrStartsWith(line, "three", false)) {
		value = 3;
		return true;
	}
	if (StrStartsWith(line, "four", false)) {
		value = 4;
		return true;
	}
	if (StrStartsWith(line, "five", false)) {
		value = 5;
		return true;
	}
	if (StrStartsWith(line, "six", false)) {
		value = 6;
		return true;
	}
	if (StrStartsWith(line, "seven", false)) {
		value = 7;
		return true;
	}
	if (StrStartsWith(line, "eight", false)) {
		value = 8;
		return true;
	}
	if (StrStartsWith(line, "nine", false)) {
		value = 9;
		return true;
	}
	if (StrStartsWith(line, "zero", false)) {
		value = 0;
		return true;
	}

	return false;
}