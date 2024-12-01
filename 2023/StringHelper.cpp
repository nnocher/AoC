#include "StringHelper.h"

bool StrStartsWith(std::string str, std::string start, bool caseSensitive) {
	if (str.length() < start.length()) {
		return false;
	}

	for (int i = 0; i < start.length(); i++) {
		if ((caseSensitive && str[i] != start[i]) ||
			(!caseSensitive && std::tolower(str[i]) != std::tolower(start[i]))) {
			return false;
		}
	}

	return true;
}

void StrSplit(std::string str, std::string split, std::vector<std::string>& r_result, bool keepEmpty) {
	r_result.clear();

	int currentIndex = 0;
	while (currentIndex < str.length()) {
		int nextSplit = str.find(split, currentIndex);

		std::string substr = str.substr(currentIndex, nextSplit - currentIndex);
		if (keepEmpty || substr.length() > 0) {
			r_result.push_back(substr);
		}

		if (nextSplit == -1) {
			break;
		}
		currentIndex = nextSplit + split.length();
	}
}

std::string StrRemoveWhitespace(std::string str) {
	std::string result = std::string(str);

	std::string::iterator end_pos = std::remove(result.begin(), result.end(), ' ');
	result.erase(end_pos, result.end());

	return result;
}

bool IsNumeric(char c) {
	return c >= '0' && c <= '9';
}