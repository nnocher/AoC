#include "Challenge11.h"

#include "Globals.h"
#include "StringHelper.h"

#include <math.h>

#define FACTOR 1000000

void Challenge11::Init() {

}

std::string Challenge11::RunChallengePart1(std::string input) {
	std::vector<std::string> lines;
	StrSplit(input, "\n", lines);

	this->ExpandMap(lines);
	this->FindGalaxies(lines);

	long totalDistance = 0;
	int currentIndex = 0;
	for (Galaxy& galaxy : this->_galaxies) {
		for (int i = ++currentIndex; i < this->_galaxies.size(); i++) {
			int distance = abs(this->_galaxies.at(i).x - galaxy.x) + abs(this->_galaxies.at(i).y - galaxy.y);
			totalDistance += distance;
		}
	}

	return std::to_string(totalDistance);
}

std::string Challenge11::RunChallengePart2(std::string input) {
	std::vector<std::string> lines;
	StrSplit(input, "\n", lines);

	//this->ExpandMap(lines, 1000000);
	this->FindGalaxies(lines);

	std::vector<int> rowFactor;
	std::vector<int> columnFactor;

	for (std::string& row : lines) {
		bool expand = true;
		for (int i = 0; i < row.length(); i++) {
			if (row.at(i) != '.') {
				expand = false;
				break;
			}
		}

		if (expand) {
			rowFactor.push_back(FACTOR);
		}
		else {
			rowFactor.push_back(1);
		}
	}

	for (int column = 0; column < lines.size(); column++) {
		bool expand = true;
		for (std::string& row : lines) {
			if (row.at(column) != '.') {
				expand = false;
				break;
			}
		}

		if (expand) {
			columnFactor.push_back(FACTOR);
		}
		else {
			columnFactor.push_back(1);
		}
	}

	long long totalDistance = 0;
	int currentIndex = 0;
	for (Galaxy& galaxy : this->_galaxies) {
		for (int i = ++currentIndex; i < this->_galaxies.size(); i++) {
			int startX = galaxy.x;
			int endX = this->_galaxies.at(i).x;
			if (startX > endX) {
				int temp = startX;
				startX = endX;
				endX = temp;
			}

			int startY = galaxy.y;
			int endY = this->_galaxies.at(i).y;
			if (startY > endY) {
				int temp = startY;
				startY = endY;
				endY = temp;
			}

			int distance = 0;
			for (int y = startY; y < endY; y++) {
				distance += rowFactor.at(y);
			}
			for (int x = startX; x < endX; x++) {
				distance += columnFactor.at(x);
			}

			totalDistance += distance;
		}
	}

	return std::to_string(totalDistance);
}

void Challenge11::ExpandMap(std::vector<std::string>& rMap, int factor) {
	for (int i = 0; i < rMap.at(0).size(); i++) {
		bool isEmpty = true;
		for (std::string line : rMap) {
			if (line.at(i) != '.') {
				isEmpty = false;
				break;
			}
		}

		if (isEmpty) {
			for (std::string& line : rMap) {
				for (int j = 0; j < factor - 1; j++) {
					line.insert(i, ".");
				}
			}
			i += factor - 1;
		}
	}

	for (int i = 0; i < rMap.size(); i++) {
		bool isEmpty = true;
		for (int j = 0; j < rMap.at(i).length(); j++) {
			if (rMap.at(i).at(j) != '.') {
				isEmpty = false;
				break;
			}
		}

		if (isEmpty) {
			for (int j = 0; j < factor - 1; j++) {
				rMap.insert(rMap.begin() + i, std::string(rMap.at(i)));
			}
			i += factor - 1;
		}
	}
}

void Challenge11::FindGalaxies(std::vector<std::string>& rMap) {
	this->_galaxies.clear();

	for (int y = 0; y < rMap.size(); y++) {
		for (int x = 0; x < rMap.at(y).length(); x++) {
			if (rMap.at(y).at(x) == '#') {
				this->_galaxies.push_back(Galaxy(x, y));
			}
		}
	}
}