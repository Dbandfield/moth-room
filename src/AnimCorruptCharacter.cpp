/*
 * AnimCorruptCharacter.cpp
 *
 *  Created on: 25 Dec 2017
 *      Author: daniel
 */

#include "AnimCorruptCharacter.h"

namespace moth
{

AnimCorruptCharacter::AnimCorruptCharacter(std::vector<Symbol*> _symbols) :
		Animator(_symbols)
{
	AnimCorruptCharacter();

}

AnimCorruptCharacter::AnimCorruptCharacter()
{
//	timer.setPeriodicEvent(changePeriod); // 0.01 seconds
	numCorrupted = adjustedNumCorrupted = 0;
	numFastCounter = 0;
	isFast = false;
	character = '_';
	timerMax = 10;

}

AnimCorruptCharacter::~AnimCorruptCharacter()
{
}

void AnimCorruptCharacter::init(int* _arg, size_t _sz)
{
	ofLog() << "[ANIM_CORRUPT_CHARACTER] - init";
	// check size of array!
	size_t sz = _sz;
	// if array has stuff in
	if (sz > 0)
	{
		// we only want the first value. Indicates
		// how many characters to corrupt.
		numCorrupted = _arg[0];

	}
	else
	{
		numCorrupted = 0;
		ofLog(OF_LOG_ERROR)
				<< "[ERROR][ANIM_CORRUPT_CHARACTER] - empty array of args";
	}

	ofLog() << "[ANIM_CORRUPT_CHARACTER] - init num corrupted is"
			<< numCorrupted;

}

void AnimCorruptCharacter::start()
{	// Now, we want to pick random characters,
// but need a vec of numbers to make sure
// we dont pick the same one twice.
	lock();

	corruptedSymbols.clear();

	std::vector<size_t> numbers;
	for (size_t i = 0; i < symbols.size(); i++)
	{
		numbers.push_back(i);
	}

	// If thearray happens to be smaller than required
	// number of characters, reduce that number. So user
	// doesnt need to worry about limiting
	// the arg
	adjustedNumCorrupted = std::min(numCorrupted, (int) numbers.size());

	// shuffle
	std::random_shuffle(numbers.begin(), numbers.end());

	// take from main vec and put in corrputed vec
	for (size_t i = 0; i < adjustedNumCorrupted; i++)
	{
		corruptedSymbols.push_back(symbols[numbers[i]]);
	}
	unlock();

	timerStart = ofGetElapsedTimeMillis();

	startThread();
}

void AnimCorruptCharacter::setArg(int* _arg, size_t _sz)
{
	init(_arg, _sz);
}

void AnimCorruptCharacter::threadedFunction()
{
	while (isThreadRunning())
	{
//		timer.waitNext();
		timer = ofGetElapsedTimeMillis() - timerStart;
		if (timer > timerMax)
		{
			int i = 0;
			lock();
			if (character == ' ')
			{
				character = '?';
			}
			else
			{
				character = ' ';
			}

			for (auto it = corruptedSymbols.begin();
					it != corruptedSymbols.end(); it++)
			{
				// 33 - 126
				//			int ran = ofRandom(33, 126);
				//			char c = ran;

				(*it)->setCharacter(character);
				i++;
			}
			unlock();

			numFastCounter++;
			if (numFastCounter > NUM_FAST)
			{
				numFastCounter = 0;
				isFast = false;
				timerMax = TIMER_SLOW;
//				changePeriod = SLOW;
//				timer.setPeriodicEvent(changePeriod);
			}
			else if (!isFast)
			{
				isFast = true;
				timerMax = TIMER_FAST;
//				changePeriod = FAST;
//				timer.setPeriodicEvent(changePeriod);
			}

			timer = 0;
			timerStart = ofGetElapsedTimeMillis();
		}

	}
}

} /* namespace moth */
