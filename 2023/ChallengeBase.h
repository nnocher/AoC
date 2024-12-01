#pragma once

#include <string>

class ChallengeBase
{
public:
	/// <summary>
	/// Runs the Challenge
	/// </summary>
	void Run(bool firstRun);

private:
	/// <summary>
	/// Read the given file into the given string
	/// </summary>
	/// <param name="fileName"></param>
	/// <param name="content"></param>
	/// <returns></returns>
	bool ReadInput(std::string fileName, std::string& content);

protected:
	/// <summary>
	/// Is called before anything else
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// Returns if the challenge has a input file configured
	/// </summary>
	/// <returns></returns>
	virtual bool HasInputFile() { return false; }

	/// <summary>
	/// Returns the default input filename
	/// </summary>
	/// <returns></returns>
	virtual std::string GetInputFile() = 0;

	/// <summary>
	/// Runs the challenge 1 with the given input.
	/// </summary>
	/// <param name="input"></param>
	/// <returns></returns>
	virtual std::string RunChallengePart1(std::string input) = 0;

	/// <summary>
	/// Runs the challenge 1 with the given input.
	/// </summary>
	/// <param name="input"></param>
	/// <returns></returns>
	virtual std::string RunChallengePart2(std::string input) = 0;
};
