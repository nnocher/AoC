#pragma once

#include "ChallengeBase.h"

#include <vector>

struct Bid {
	std::string hand;
	int bid;

public:
	Bid() : hand(), bid(0) {};
	Bid(std::string hand, int bid) : hand(hand), bid(bid) {};
};

enum HandValue {
	eHighCard = 0, 
	eOnePair = 15,
	eTwoPair = 16,
	eThreeOfAKind = 17,
	eFullHouse = 18,
	eFourOfAKind = 19,
	eFiveOfAKind = 20,
};

class Challenge7 : public ChallengeBase {
private:
	std::vector<Bid> _bids;

protected:
	bool HasInputFile() { return true; }
	std::string GetInputFile() { return "Challenge7.txt"; }

	void Init();
	std::string RunChallengePart1(std::string input);
	std::string RunChallengePart2(std::string input);

private:
	void ReadBids(std::string input);
	
public:
	static int CompareHand1(std::string hand1, std::string hand2);
	static int GetCardValue1(char card);
	static HandValue GetHandValue1(std::string hand);

	static int CompareHand2(std::string hand1, std::string hand2);
	static int GetCardValue2(char card);
	static HandValue GetHandValue2(std::string hand);
};

struct Bid_Sort1 {
	inline bool operator() (const Bid& rBid1, const Bid& rBid2) {
		return Challenge7::CompareHand1(rBid1.hand, rBid2.hand) == -1;
	}
};

struct Bid_Sort2 {
	inline bool operator() (const Bid& rBid1, const Bid& rBid2) {
		return Challenge7::CompareHand2(rBid1.hand, rBid2.hand) == -1;
	}
};