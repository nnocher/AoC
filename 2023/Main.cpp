#include <iostream>

#include "Globals.h"
#include "Challenges.h"

// Auto select day on run
#define AUTO_SELECT 10
#define AUTO_FIRST false

int main() {
	int selectedDay = 0;
	bool validSelection = true;

	ChallengeBase** challenges = GetChallenges();

#ifdef AUTO_SELECT

	PrintLine("AUTO_SELECT");
	PrintSeparator();

	if (challenges[AUTO_SELECT]) {
		challenges[AUTO_SELECT]->Run(AUTO_FIRST);
	}
	else {
		Print("Invalid AUTO_SELECT");
	}
	

	return 99;

#endif

	// Day selection
	do {
		selectedDay = PromptNumeric("Select day (-1 to exit): ");

		if (selectedDay == -1) {
			return 0;
		}

		if (selectedDay < 1 || selectedDay > 24) {
			PrintLine("Invalid day. Please select a number between 1 and 24.");
		}
		else if (!challenges[selectedDay - 1]) {
			PrintLine("Day not defined. Please select a different day.");
		}
		else {
			validSelection = true;
		}
	} while (!validSelection);

	std::string result = Prompt("First run? [y/n] ");
	bool firstRun = false;
	if (result == "n") {
		PrintLine("Running second run.");
	}
	else {
		PrintLine("Running first run.");
		firstRun = true;
	}

	challenges[selectedDay - 1]->Run(firstRun);

	return 1;
};