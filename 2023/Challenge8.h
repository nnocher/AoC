#pragma once

#include "ChallengeBase.h"

#include <vector>

struct Node {
	std::string key;
	std::string leftKey;
	std::string rightKey;

	Node* left;
	Node* right;
};

class Challenge8 : public ChallengeBase {

	std::vector<Node> _map;
	bool _optimized = false;

	Node* _firstNode;
	Node* _finalNode;

	std::vector<Node*> _startNodes;

protected:
	bool HasInputFile() { return true; }
	std::string GetInputFile() { return "Challenge8.txt"; }

	void Init();
	std::string RunChallengePart1(std::string input);
	std::string RunChallengePart2(std::string input);

private:
	void ReadMap(const std::vector<std::string>::iterator begin, const std::vector<std::string>::iterator end);
	void OptimizeMap();
	unsigned long long NavigateMap(const std::string instructionStr);
	unsigned long long NavigateMapPart2(const std::string instructionStr);
	bool CheckNodes(const std::vector<Node*>& rNodes, const int nodeCount);
	bool CheckNodes(const int* pNodes, const int nodeCount);

	unsigned long long CalcResult(const int* pNodes, const int nodeCount);
};