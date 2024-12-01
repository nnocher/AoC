#pragma once

#include <iostream>
#include <string>

#include "StringHelper.h"

#define TOSTRING(i) std::to_string(i)

#define SUBSTRING(str, start, end) str.substr(start, end - (start))

/// <summary>
/// Print a message to the console
/// </summary>
/// <param name="msg"></param>
void Print(std::string msg);

/// <summary>
/// Print a message line to the console
/// </summary>
/// <param name="msg"></param>
void PrintLine(std::string msg);

/// <summary>
/// Print a separator line to the console
/// </summary>
/// <param name="length">Number of characters to print</param>
/// <param name="c">Character to print</param>
void PrintSeparator(const int length = 10, const char c = '-');

/// <summary>
/// Prints an input prompt and retuns the input.
/// </summary>
/// <param name="prompt"></param>
/// <returns></returns>
std::string Prompt(std::string prompt);

/// <summary>
/// Prints an input prompt and returns the entered numeric value as a double
/// </summary>
/// <param name="prompt"></param>
/// <returns></returns>
double PromptNumeric(std::string prompt);
