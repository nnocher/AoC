#include "ChallengeBase.h"

#include "Globals.h"
#include <fstream>
#include <sstream>
#include <chrono>

void ChallengeBase::Run(bool firstRun) {
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	
	this->Init();

	std::string input = "";
	if (!this->HasInputFile() || !ReadInput(this->GetInputFile(), input))
	{
		PrintLine("No input file read.");
		std::string input = Prompt("Input: ");
	}

	PrintLine("Running challenge...");
	PrintSeparator();

	std::string result;

	if (firstRun) {
		result = this->RunChallengePart1(input);
	}
	else {
		result = this->RunChallengePart2(input);
	}

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	PrintSeparator();

	Print("Result: " + result);

	PrintLine("\n");

	double elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.0;
	PrintLine("Runtime: " + std::to_string(elapsedTime) + "ms");
	PrintSeparator();
}

bool ChallengeBase::ReadInput(std::string fileName, std::string& content) {
	std::ifstream stream(fileName);

	try {
		if (stream.is_open()) {
			std::stringstream buffer;
			buffer << stream.rdbuf();
			content = buffer.str();
			return true;
		}
	}
	catch (std::exception ex) {
		PrintSeparator();
		PrintLine(ex.what());
		PrintSeparator();
	}

	PrintLine("[!]Failed to open File!");
	return false;
}
