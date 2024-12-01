#pragma once

#include "ChallengeBase.h"

#include <vector>

enum Direction {
	eNone = 0,		// 0000

	eRight = 1,		// 0001
	eDown = 2,		// 0010
	eLeft = 4,		// 0100
	eUp = 8,		// 1000

	eRightDown = 3,	// 0011
	eLeftDown = 6,	// 0101
	eRightUp = 9,	// 1001
	eLeftUp = 12,	// 1100
};

struct Coord {
	int x;
	int y;
	char type;

	bool outside;

	Coord* pNext;
	Coord* pPrev;

	Coord(int type, int x, int y) : 
		type(type), 
		x(x), 
		y(y),
		outside(false),
		pNext(NULL),
		pPrev(NULL) {}

	bool IsBorder() const {
		return pNext != NULL;
	}
};

class Challenge10 : public ChallengeBase {
private:
	std::vector<std::vector<Coord*>> _map;

	Coord* _pStart;
	int _stepCount;

public:
	~Challenge10();

protected:
	bool HasInputFile() { return true; }
	std::string GetInputFile() { return "Challenge10.txt"; }

	void Init();
	std::string RunChallengePart1(std::string input);
	std::string RunChallengePart2(std::string input);

private:
	void BuildMap(std::string mapStr);
	void LinkMap();

	void MapOutside();

	bool GetCoord(Coord*& rpCurrent, Direction direction, Coord*& rpNext);
	short GetDirectionMask(char type);
	char GetDirectionChar(short mask);
	Direction InvertDirection(Direction original);

	void ClearMap();

	void PrintMap();
};