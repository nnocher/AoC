#include "Challenge5.h"

#include "Globals.h"
#include <string>
#include <boost/thread/thread.hpp>

std::string Challenge5::GetInputFile() {
	return "Challenge5.txt";
	//return "Test.txt";
}

std::string Challenge5::RunChallengePart1(std::string input) {
	this->ReadInput(input);

	PrintLine(std::to_string(this->_seeds.size()) + " seeds found.");
	PrintLine(std::to_string(this->_maps.size()) + " maps found.");

	BASE_TYPE lowestPosition = ULLONG_MAX;

	// -- part 1
	for (std::vector<BASE_TYPE>::iterator it = this->_seeds.begin(); it < this->_seeds.end(); it++) {
		BASE_TYPE position = this->MapSeed(*it);
		if (position < lowestPosition) {
			lowestPosition = position;
		}
	}

	return std::to_string(lowestPosition);
}

std::string Challenge5::RunChallengePart2(std::string input) {
	this->ReadInput(input);

	PrintLine(std::to_string(this->_seeds.size()) + " seeds found.");
	PrintLine(std::to_string(this->_maps.size()) + " maps found.");

	BASE_TYPE lowestPosition = LLONG_MAX;

	std::vector<ThreadResult*> results;
	int id = 0;
	for (std::vector<BASE_TYPE>::iterator it = this->_seeds.begin(); it < this->_seeds.end(); it++) {
		BASE_TYPE start = *it;
		BASE_TYPE range = *(++it);

		while (*this->_pThreadCount > MAX_WORKERS) {
			boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
		}

		*this->_pThreadCount = *this->_pThreadCount + 1;

		ThreadResult* result = new ThreadResult();
		result->pResult = new BASE_TYPE(0);
		result->thread = boost::thread(&Challenge5::RunSeedRange, this, id++, start, range, result->pResult);
		results.push_back(result);
	}

	for (std::vector<ThreadResult*>::iterator it = results.begin(); it < results.end(); it++) {
		ThreadResult* result = *it;
		result->thread.join();

		if (lowestPosition > *result->pResult) {
			lowestPosition = *result->pResult;
		}

		delete result->pResult;
		delete result;
	}
	results.clear();
	
	return std::to_string(lowestPosition);
}

void Challenge5::RunSeedRange(int id, BASE_TYPE start, BASE_TYPE range, BASE_TYPE* pRange) {
	Print("Started Worker " + std::to_string(id) + " for " + std::to_string(range) + " elements.\n");

	BASE_TYPE lowestLocation = ULLONG_MAX;
	
	double lastPing = 0;

	for (int seed = 0; seed < range; seed++) {
		BASE_TYPE result = this->MapSeed(seed + start);
		if (lowestLocation > result) {
			lowestLocation = result;
		}

		double progress = (seed / (double)range) * 100.0;
		if (progress > lastPing + 1) {
			lastPing = progress + 1;
			PrintLine("Worker " + std::to_string(id) + " at " + std::to_string((int)lastPing) + "%");
		}
	}

	PrintLine("Worker " + std::to_string(id) + " finished.");
	*pRange = lowestLocation;
	*this->_pThreadCount = *this->_pThreadCount - 1;
}

void Challenge5::Init()
{
	this->_pThreadCount = new int(0);
	this->_seeds.clear();

	for (int i = 0; i < this->_maps.size(); i++) {
		this->_maps.at(i).clear();
	}
	this->_maps.clear();
}

void Challenge5::ReadInput(std::string input) {
	int inputLength = input.length();
	std::string sectionDel = "\n\n";
	int lastSectionEnd = input.find(sectionDel);
	
	// Read Seeds
	std::string seedSubstr = input.substr(0, lastSectionEnd);
	bool firstRun = true;
	int nextEnd = 0;
	do {
		std::string del = " ";
		nextEnd = seedSubstr.find(del);

		// Skip first
		if (!firstRun) {
			this->_seeds.push_back(STR_TO_BASE(seedSubstr.substr(0, nextEnd)));
		}

		seedSubstr = seedSubstr.substr(nextEnd + 1);
		firstRun = false;
	} while (nextEnd > 0);

	// Read maps
	do {
		int currentSectionEnd = input.find(sectionDel, lastSectionEnd + 2);
		std::string currentStr = SUBSTRING(input, lastSectionEnd + 2, currentSectionEnd);

		std::vector<Map> currentMap;

		firstRun = true;
		nextEnd = 0;
		do {
			std::string del = "\n";
			nextEnd = currentStr.find(del);

			// Skip first
			if (!firstRun) {
				Map map;
				del = " ";

				int startDestEnd = currentStr.find(del);
				map.startDest = STR_TO_BASE(currentStr.substr(0, startDestEnd));

				int startSourceEnd = currentStr.find(del, startDestEnd + 1);
				map.startSource = STR_TO_BASE(SUBSTRING(currentStr, startDestEnd + 1, startSourceEnd));

				map.length = STR_TO_BASE(SUBSTRING(currentStr, startSourceEnd + 1, nextEnd));

				currentMap.push_back(map);
			}

			currentStr = currentStr.substr(nextEnd + 1);
			firstRun = false;
		} while (nextEnd > 0);

		_maps.push_back(currentMap);
		lastSectionEnd = currentSectionEnd;
	} while (lastSectionEnd != -1);
}

BASE_TYPE Challenge5::MapSeed(BASE_TYPE seed) {
	int currentInput = seed;

	for (std::vector<std::vector<Map>>::iterator it = this->_maps.begin(); it < this->_maps.end(); it++) {
		for (std::vector<Map>::iterator itMap = (*it).begin(); itMap < (*it).end(); itMap++) {
			int offset = currentInput - itMap->startSource;

			if (offset >= 0 && offset < itMap->length) {
				// Correct map
				currentInput = itMap->startDest + offset;
				break;
			}
		}
	}

	return currentInput;
}