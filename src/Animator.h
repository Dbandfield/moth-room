#pragma once

#include <ofMain.h>

#include <vector>

#include "Symbol.h"

namespace moth
{

class Animator : public ofThread
{
public:
	Animator();
	Animator(std::vector<Symbol*> _symbols);
	virtual ~Animator();

	void setOnEnd(void(*_f)());
//	void setLoop(bool _loop);

	void setSymbols(std::vector<Symbol*> _symbols);

	virtual void init(int* _arg, size_t _sz)= 0;
	virtual void start()= 0;
	virtual void threadedFunction()= 0;

	virtual void setArg(int* _arg, size_t _sz)=0;


protected:
	void (*onEnd)();

	std::vector<Symbol*> symbols;
//	bool loop;
	bool playing;

	long timer;
	long timerStart;
	long timerMax;

//	ofTimer timer;

};

} /* namespace moth */

