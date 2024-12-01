#pragma once

#include "ChallengeBase.h"

#include "Challenge1.h"
#include "Challenge2.h"
#include "Challenge3.h"
#include "Challenge4.h"
#include "Challenge5.h"
#include "Challenge6.h"
#include "Challenge7.h"
#include "Challenge8.h"
#include "Challenge9.h"
#include "Challenge10.h"
#include "Challenge11.h"

/// <summary>
/// Returns the array of Challenges for each day.
/// NULL if no challenge is defined
/// </summary>
/// <returns></returns>
ChallengeBase** GetChallenges() {
	ChallengeBase** result = new ChallengeBase*[24] {NULL};

	result[0] = new Challenge1();
	result[1] = new Challenge2();
	result[2] = new Challenge3();
	result[3] = new Challenge4();
	result[4] = new Challenge5();
	result[5] = new Challenge6();
	result[6] = new Challenge7();
	result[7] = new Challenge8();
	result[8] = new Challenge9();
	result[9] = new Challenge10();
	result[10] = new Challenge11();

	return result;
};