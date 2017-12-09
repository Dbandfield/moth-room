#pragma once

#include <ofMain.h>

#include "GameControl.h"

namespace moth
{

class GameControl;

class Option
{
public:
	Option();
	virtual ~Option();

	void setCallback(GameControl *_gameControl, void(GameControl::*_f)(unsigned int), unsigned int _arg);
	void onSelect();

protected:

	GameControl *gameControl;
	void (GameControl::*f)(unsigned int);
	ofRectangle bounds;
	unsigned int callbackArg;
};

} /* namespace moth */

