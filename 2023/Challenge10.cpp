#include "Challenge10.h"

#include <vector>

#include "StringHelper.h"
#include "Globals.h"

Challenge10::~Challenge10() {
	this->ClearMap();
}

void Challenge10::Init() {

}

std::string Challenge10::RunChallengePart1(std::string input) {
	this->BuildMap(input);

	return std::to_string(this->_stepCount / 2);
}

std::string Challenge10::RunChallengePart2(std::string input) {
	this->BuildMap(input);
	this->MapOutside();

	this->PrintMap();

	// Count insides
	int count = 0;
	for (std::vector<Coord*> row : this->_map) {
		for (Coord* pCoord : row) {
			if (!pCoord->IsBorder() && !pCoord->outside) {
				count++;
			}
		}
	}

	return std::to_string(count);
}

void Challenge10::MapOutside() {
	int width = this->_map.at(0).size();
	int height = this->_map.size();
	
	// Loop around outside
	for (int y = 0; y < height; y++) {
		int borderCount = 0;
		Direction openDirection = eNone;

		for (int x = 0; x < width; x++) {
			Coord* pCurrent = this->_map.at(y).at(x);

			if (pCurrent->IsBorder()) {
				char type = pCurrent->type;
				if (type == 'S') {
					short tempDir = 0;
					Coord* pTemp;

					if (this->GetCoord(pCurrent, eRight, pTemp)) {
						tempDir |= eRight;
					}
					if (this->GetCoord(pCurrent, eDown, pTemp)) {
						tempDir |= eDown;
					}
					if (this->GetCoord(pCurrent, eLeft, pTemp)) {
						tempDir |= eLeft;
					}
					if (this->GetCoord(pCurrent, eUp, pTemp)) {
						tempDir |= eUp;
					}

					type = this->GetDirectionChar(tempDir);
				}

				if (type != '-') {
					if (type == '|') {
						borderCount++;
						openDirection = eNone;
						continue;
					}

					Direction currentOpenDirection = (Direction) (this->GetDirectionMask(type) & (eUp | eDown));
					if (openDirection == eNone || currentOpenDirection == openDirection) {
						borderCount++;
						openDirection = currentOpenDirection;
					}
				}
				continue;
			}

			pCurrent->outside = borderCount % 2 == 0;
		}
	}
}

void Challenge10::BuildMap(std::string mapStr) {
	std::vector<std::string> lines;
	StrSplit(mapStr, "\n", lines);

	int y = 0;
	for (std::string str : lines) {
		int x = 0;
		std::vector<Coord*> coords;
		for (char c : str) {
			Coord* coord = new Coord(c, x, y);

			if (c == 'S') {
				// starting point
				this->_pStart = coord;
			}

			coords.push_back(coord);
			x++;
		}

		this->_map.push_back(coords);
		y++;
	}

	this->LinkMap();
}

void Challenge10::LinkMap() {
	Coord* pCurrent = this->_pStart;
	Coord* pPrevious = NULL;
	Direction lastDirection = eNone;

	int steps = 0;

	do {
		if (lastDirection == eNone) {
			// Start case
			if (this->GetCoord(pCurrent, eRight, pCurrent->pNext)) {
				lastDirection = eRight;
			}
			else if (this->GetCoord(pCurrent, eDown, pCurrent->pNext)) {
				lastDirection = eDown;
			}
			else if (this->GetCoord(pCurrent, eLeft, pCurrent->pNext)) {
				lastDirection = eLeft;
			}
			else if (this->GetCoord(pCurrent, eUp, pCurrent->pNext)) {
				lastDirection = eUp;
			}
			else {
				// ??????
				throw std::exception();
			}
		}
		else {
			lastDirection = (Direction)(this->GetDirectionMask(pCurrent->type) & ~this->InvertDirection(lastDirection));
			this->GetCoord(pCurrent, lastDirection, pCurrent->pNext);
		}

		pCurrent->pNext->pPrev = pCurrent;
		pCurrent = pCurrent->pNext;
		steps++;
	} while (pCurrent != this->_pStart);

	this->_stepCount = steps;
}

bool Challenge10::GetCoord(Coord*& rpCurrent, Direction direction, Coord*& rpNext) {
	int x = rpCurrent->x;
	int y = rpCurrent->y;

	switch (direction) {
	case eRight:
		x++;
		break;
	case eDown:
		y++;
		break;
	case eLeft:
		x--;
		break;
	case eUp:
		y--;
		break;
	}

	if (y < 0 || y >= this->_map.size()) {
		return false;
	}
	if (x < 0 || x >= this->_map.at(0).size()) {
		return false;
	}

	Coord* pNext = this->_map.at(y).at(x);
	if ((this->GetDirectionMask(pNext->type) & this->InvertDirection(direction)) != 0) {
		rpNext = pNext;
		return true;
	}

	return false;
}

short Challenge10::GetDirectionMask(char type) {
	switch (type) {
	case '|':
		return (eUp | eDown);
	case '-':
		return (eLeft | eRight);
	case 'L':
		return (eUp | eRight);
	case 'J':
		return (eUp | eLeft);
	case '7':
		return (eDown | eLeft);
	case 'F':
		return (eDown | eRight);
	case 'S':
		return (eLeft | eDown | eRight | eUp);
	default:
		return eNone;
	}
}

char Challenge10::GetDirectionChar(short mask) {
	switch (mask) {
	case (eUp | eDown):
		return '|';
	case (eLeft | eRight):
		return '-';
	case (eUp | eRight):
		return 'L';
	case (eUp | eLeft):
		return 'J';
	case (eDown | eRight):
		return 'F';
	case (eDown | eLeft):
		return '7';
	default:
		return '.';
	}
}

Direction Challenge10::InvertDirection(Direction original) {
	switch (original) {
	case eRight:
		return eLeft;
	case eLeft:
		return eRight;
	case eUp:
		return eDown;
	case eDown:
		return eUp;
	default:
		return eNone;
	}
}

void Challenge10::ClearMap() {
	for (std::vector<Coord*> row : this->_map) {
		for (int x = 0; x < row.size(); x++) {
			if (row.at(x)) {
				delete row.at(x);
			}
		}

		row.clear();
	}

	this->_map.clear();
}

void Challenge10::PrintMap() {
	for (std::vector<Coord*> row : this->_map) {
		for (Coord* pCoord : row) {
			if (pCoord->outside) {
				Print("O");
			}
			else if (!pCoord->IsBorder()) {
				Print("I");
			}
			else {
				Print(std::string(1, pCoord->type));
			}
		}

		Print("\n");
	}
}