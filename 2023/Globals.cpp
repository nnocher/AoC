#include "Globals.h"

void Print(std::string msg) {
	std::cout << msg;
}

void PrintLine(std::string msg) {
	std::cout << msg << std::endl;
}

void PrintSeparator(const int length, const char c) {
	for (int i = 0; i < length; i++) {
		std::cout << c;
	}
	std::cout << std::endl;
}

std::string Prompt(std::string prompt) {
	std::cout << prompt << std::flush;

	std::string input;
	std::cin >> input;

	return input;
}

double PromptNumeric(std::string prompt) {
	bool isValid = false;
	double result = 0;

	while (!isValid) {
		std::string resultStr = Prompt(prompt);

		try
		{
			result = std::stod(resultStr);
			isValid = true;
		}
		catch (std::exception e)
		{
			PrintLine("Invalid input.");
		}
	}

	return result;
};