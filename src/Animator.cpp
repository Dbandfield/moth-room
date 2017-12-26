/*
 * Animator.cpp
 *
 *  Created on: 25 Dec 2017
 *      Author: daniel
 */

#include "Animator.h"

namespace moth
{

Animator::Animator(std::vector<Symbol*> _symbols):	Animator()
{
//	loop = false;
	symbols = _symbols;
}

Animator::Animator()
{
	playing = false;
	onEnd = [](){};
	timer = 0;
	timerStart = 0;
	timerMax = 0;
}

Animator::~Animator()
{
}

void Animator::setSymbols(std::vector<Symbol*> _symbols)
{
	ofLog() << "[ANIMATOR] - setSymbols";

	symbols = _symbols;
}

void Animator::setOnEnd(void(*_f)())
{
	onEnd = _f;
}

//void Animator::setLoop(bool _loop)
//{
//	loop = _loop;
//}

} /* namespace moth */
