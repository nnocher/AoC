#pragma once

#include "ChallengeBase.h"

#include <vector>
#include <boost/thread/thread.hpp>

#define BASE_TYPE unsigned long long
#define STR_TO_BASE(str) std::stoull(str)

#define MAX_WORKERS 6

/// <summary>
/// Struct for a single map element
/// </summary>
struct Map {
	BASE_TYPE startDest;
	BASE_TYPE startSource;
	BASE_TYPE length;
};

struct ThreadResult {
	BASE_TYPE* pResult;
	boost::thread thread;
};

class Challenge5 : public ChallengeBase {
	/// <summary>
	/// Vector of the entered seeds
	/// </summary>
	std::vector<BASE_TYPE> _seeds;

	/// <summary>
	/// Vector of each map group
	/// </summary>
	std::vector<std::vector<Map>> _maps;

	int* _pThreadCount;

protected:
	void Init();

	bool HasInputFile() { return true; }

	std::string GetInputFile();

	std::string RunChallengePart1(std::string input);
	std::string RunChallengePart2(std::string input);

private:
	void RunSeedRange(int id, BASE_TYPE start, BASE_TYPE range, BASE_TYPE* pResult);

	/// <summary>
	/// Reads the input string into the _seeds and _maps
	/// </summary>
	/// <param name="input"></param>
	void ReadInput(std::string input);

	/// <summary>
	/// Map a seed to it's final value
	/// </summary>
	/// <param name="seed"></param>
	/// <returns></returns>
	BASE_TYPE MapSeed(BASE_TYPE seed);
};