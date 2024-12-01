#include "Challenge7.h"

#include "StringHelper.h"
#include <boost/range/algorithm.hpp>
#include <list>

void Challenge7::Init() {

}

std::string Challenge7::RunChallengePart1(std::string input) {
	this->ReadBids(input);
	std::sort(this->_bids.begin(), this->_bids.end(), Bid_Sort1());

	int totalWinnings = 0;
	for (int i = 0; i < this->_bids.size(); i++) {
		totalWinnings += (i + 1) * this->_bids.at(i).bid;
	}

	return std::to_string(totalWinnings);
}

std::string Challenge7::RunChallengePart2(std::string input) {
	this->ReadBids(input);
	std::sort(this->_bids.begin(), this->_bids.end(), Bid_Sort2());

	int totalWinnings = 0;
	for (int i = 0; i < this->_bids.size(); i++) {
		totalWinnings += (i + 1) * this->_bids.at(i).bid;
	}

	return std::to_string(totalWinnings);
}

void Challenge7::ReadBids(std::string input) {
	this->_bids.clear();

	std::vector<std::string> lines;
	StrSplit(input, "\n", lines);

	for (auto line : lines) {
		int separator = line.find(' ');
		this->_bids.push_back(Bid(line.substr(0, separator), std::stoi(line.substr(separator + 1))));
	}
}

// -------- PART 1 ------------------------------------------------------------

int Challenge7::GetCardValue1(char c) {
	if (c >= '2' && c <= '9') {
		return c - '2';
	}

	switch (c) {
		case 'T':
			return 8;
		case 'J':
			return 9;
		case 'Q':
			return 10;
		case 'K':
			return 11;
		case 'A':
			return 12;
	}

	return -1;
}

HandValue Challenge7::GetHandValue1(std::string hand) {
	int cards[13];
	std::fill_n(cards, 13, 0);

	for (char card : hand) {
		cards[Challenge7::GetCardValue1(card)]++;
	}

	bool hasPair = false;
	bool hasTriplet = false;
	for (int i = 0; i < 13; i++) {
		if (cards[i] == 5) {
			return eFiveOfAKind;
		}
		else if (cards[i] == 4) {
			return eFourOfAKind;
		}
		else if (cards[i] == 3) {
			hasTriplet = true;
		}
		else if (cards[i] == 2) {
			if (hasPair) {
				return eTwoPair;
			}

			hasPair = true;
		}
	}

	if (hasTriplet) {
		return hasPair ? eFullHouse : eThreeOfAKind;
	}
	else if (hasPair) {
		return eOnePair;
	}

	return eHighCard;
}

int Challenge7::CompareHand1(std::string hand1, std::string hand2) {
	HandValue handValue1 = Challenge7::GetHandValue1(hand1);
	HandValue handValue2 = Challenge7::GetHandValue1(hand2);

	if (handValue1 > handValue2) {
		return 1;
	}
	if (handValue1 < handValue2) {
		return -1;
	}

	// hand type are the same
	for (int i = 0; i < hand1.length(); i++) {
		int cardValue1 = Challenge7::GetCardValue1(hand1[i]);
		int cardValue2 = Challenge7::GetCardValue1(hand2[i]);

		if (cardValue1 > cardValue2) {
			return 1;
		}
		if (cardValue1 < cardValue2) {
			return -1;
		}
	}

	return 0;
}

// -------- PART 2 ------------------------------------------------------------

int Challenge7::GetCardValue2(char c) {
	if (c >= '2' && c <= '9') {
		return c - '1';
	}

	switch (c) {
	case 'T':
		return 9;
	case 'J':
		return 0;
	case 'Q':
		return 10;
	case 'K':
		return 11;
	case 'A':
		return 12;
	}

	return -1;
}

HandValue Challenge7::GetHandValue2(std::string hand) {
	int cards[13];
	std::fill_n(cards, 13, 0);

	int highestIndex = -1;
	int highestCount = 0;
	for (char card : hand) {
		int cardValue = Challenge7::GetCardValue2(card);

		if (++cards[cardValue] > highestCount && cardValue != 0) {
			highestCount = cards[cardValue];
			highestIndex = cardValue;
		}
	}

	if (cards[0] == 5) {
		// 5 joker
		return eFiveOfAKind;
	}

	bool hasPair = false;
	bool hasTwoPair = false;
	bool hasTriplet = false;
	for (int i = 1; i < 13; i++) {
		int cardCount = cards[i];
		if (cardCount == 0) {
			continue;
		}

		if (i == highestIndex) {
			cardCount += cards[0];
		}

		if (cardCount == 5) {
			return eFiveOfAKind;
		}
		else if (cardCount == 4) {
			return eFourOfAKind;
		}
		else if (cardCount == 3) {
			hasTriplet = true;
		}
		else if (cardCount == 2) {
			if (hasPair) {
				hasTwoPair = true;
			}
			hasPair = true;
		}
	}

	if (hasTriplet) {
		return hasPair ? eFullHouse : eThreeOfAKind;
	}
	else if (hasTwoPair) {
		return eTwoPair;
	}
	else if (hasPair) {
		return eOnePair;
	}

	return eHighCard;
}

int Challenge7::CompareHand2(std::string hand1, std::string hand2) {
	HandValue handValue1 = Challenge7::GetHandValue2(hand1);
	HandValue handValue2 = Challenge7::GetHandValue2(hand2);

	if (handValue1 > handValue2) {
		return 1;
	}
	if (handValue1 < handValue2) {
		return -1;
	}

	// hand type are the same
	for (int i = 0; i < hand1.length(); i++) {
		int cardValue1 = Challenge7::GetCardValue2(hand1[i]);
		int cardValue2 = Challenge7::GetCardValue2(hand2[i]);

		if (cardValue1 > cardValue2) {
			return 1;
		}
		if (cardValue1 < cardValue2) {
			return -1;
		}
	}

	return 0;
}