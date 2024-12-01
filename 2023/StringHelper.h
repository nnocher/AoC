#pragma once

#include <vector>
#include <string>

bool StrStartsWith(std::string str, std::string start, bool caseSensitive = true);

void StrSplit(std::string str, std::string split, std::vector<std::string>& r_result, bool keepEmpty = true);

std::string StrRemoveWhitespace(std::string str);

bool IsNumeric(char c);