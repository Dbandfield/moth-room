#pragma once

#include <algorithm>

#include "Animator.h"

namespace moth
{

class AnimCorruptCharacter: public Animator
{
public:
	AnimCorruptCharacter();
	AnimCorruptCharacter(std::vector<Symbol*> _symbols);
	virtual ~AnimCorruptCharacter();

	void init(int* _arg, size_t _sz);
	void start();
	void threadedFunction();
	void setArg(int* _arg, size_t _sz);


protected:
	int numCorrupted;
	int adjustedNumCorrupted;
	std::vector<Symbol*> corruptedSymbols;
//	const long SLOW = 1000000000;
//	const long FAST = 100000000;
	//	long changePeriod = SLOW;

	const long TIMER_FAST = 10;
	const long TIMER_SLOW = 100;
	const unsigned int NUM_FAST = 5;
	unsigned int numFastCounter;
	bool isFast;

	char character;

	long timer;
	long timerStart;
	long timerMax;
};

} /* namespace moth */
