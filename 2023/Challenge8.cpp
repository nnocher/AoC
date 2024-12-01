#include "Challenge8.h"

#include "StringHelper.h"

#define FIRST_KEY "AAA"
#define FINAL_KEY "ZZZ"

void Challenge8::Init() {

}

std::string Challenge8::RunChallengePart1(std::string input) {
	std::vector<std::string> lines;
	StrSplit(input, "\n", lines, false);

	this->ReadMap(++lines.begin(), lines.end());
	unsigned long long result = this->NavigateMap(*lines.begin());

	return std::to_string(result);
}

std::string Challenge8::RunChallengePart2(std::string input) {
	std::vector<std::string> lines;
	StrSplit(input, "\n", lines, false);

	this->ReadMap(++lines.begin(), lines.end());
	unsigned long long result = this->NavigateMapPart2(*lines.begin());

	return std::to_string(result);
}

void Challenge8::ReadMap(const std::vector<std::string>::iterator begin, const std::vector<std::string>::iterator end) {
	this->_map.clear();
	this->_optimized = false;

	for (std::vector<std::string>::iterator current = begin; current < end; current++) {
		std::string str = *current;
		int separator = str.find(' ');
		int nextStart = separator + 4;
		int nextSeparator = str.find(',');
		
		Node node;
		node.key = str.substr(0, separator);
		node.leftKey = str.substr(nextStart, nextSeparator - nextStart);
		node.rightKey = str.substr(nextSeparator + 2, str.length() - (nextSeparator + 3));

		this->_map.push_back(node);
	}
}

void Challenge8::OptimizeMap() {
	this->_startNodes.clear();

	for (std::vector<Node>::iterator node = this->_map.begin(); node < this->_map.end(); node++) {
		for (std::vector<Node>::iterator innerNode = this->_map.begin(); innerNode < this->_map.end() && node->left && node->right; innerNode++) {
			if (node->leftKey == innerNode->key) {
				node->left = &*innerNode;
			}
			if (node->rightKey == innerNode->key) {
				node->right = &*innerNode;
			}	
		}

		if (node->key == FINAL_KEY) {
			this->_finalNode = &*node;
		}
		if (node->key == FIRST_KEY) {
			this->_firstNode = &*node;
		}

		if (node->key[2] == 'A') {
			this->_startNodes.push_back(&*node);
		}
	}
}

unsigned long long Challenge8::NavigateMap(const std::string instructionStr) {
	if (!this->_optimized) {
		this->OptimizeMap();
	}

	unsigned long long steps = 0;
	Node* pCurrentNode = this->_firstNode;

	std::vector<char> instructions(instructionStr.begin(), instructionStr.end());
	char* it = &*instructions.begin();
	unsigned int index = 0;
	unsigned int instructionCount = instructions.size();
	while (pCurrentNode != this->_finalNode) {
		if (it[index] == 'L') {
			pCurrentNode = pCurrentNode->left;
		}
		else {
			pCurrentNode = pCurrentNode->right;
		}

		steps++;
		if (++index == instructionCount) {
			index = 0;
		}
	}

	return steps;
}

unsigned long long Challenge8::NavigateMapPart2(const std::string instructionStr) {
	if (!this->_optimized) {
		this->OptimizeMap();
	}

	unsigned long long steps = 1;
	std::vector<Node*> nodes(this->_startNodes.begin(), this->_startNodes.end());
	int nodeCount = nodes.size();

	int* results = new int[nodeCount];
	std::fill_n(results, nodeCount, 0);

	std::vector<char> instructions(instructionStr.begin(), instructionStr.end());
	char* it = &*instructions.begin();
	unsigned int index = 0;
	unsigned int instructionCount = instructions.size();
	while (!this->CheckNodes(results, nodeCount)) {
		if (it[index] == 'L') {
			for (int i = 0; i < nodeCount; i++) {
				if (results[i] != 0) {
					continue;
				}

				nodes[i] = nodes[i]->left;

				if (nodes[i]->key[2] == 'Z') {
					results[i] = steps;
				}
			}
		}
		else {
			for (int i = 0; i < nodeCount; i++) {
				if (results[i] != 0) {
					continue;
				}

				nodes[i] = nodes[i]->right;

				if (nodes[i]->key[2] == 'Z') {
					results[i] = steps;
				}
			}
		}

		steps++;
		if (++index == instructionCount) {
			index = 0;
		}
	}

	return this->CalcResult(results, nodeCount);
}

unsigned long long Challenge8::CalcResult(const int* pNodes, const int nodeCount) {
	unsigned long long pHighest = 0;

	for (int i = 0; i < nodeCount; i++) {
		if (pNodes[i] > pHighest) {
			pHighest = pNodes[i];
		}
	}

	unsigned long long result = 0;
	bool found = false;
	while (!found) {
		found = true;
		result += pHighest;
		for (int i = 0; i < nodeCount; i++) {
			if (result % pNodes[i] != 0) {
				found = false;
				break;
			}
		}
	}

	return result;
}

bool Challenge8::CheckNodes(const int* pNodes, const int nodeCount) {
	for (int i = 0; i < nodeCount; i++) {
		if (pNodes[i] == 0) {
			return false;
		}
	}

	return true;
}

bool Challenge8::CheckNodes(const std::vector<Node*>& rNodes, const int nodeCount) {
	for (int i = 0; i < nodeCount; i++) {
		if (rNodes[i]->key[2] != 'Z') {
			return false;
		}
	}

	return true;
}