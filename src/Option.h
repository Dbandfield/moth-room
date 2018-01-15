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

	void setCallback(GameControl *_gameControl, void(GameControl::*_f)(Args), Args);
	void onSelect();

protected:

	GameControl *gameControl;
	void (GameControl::*f)(Args);
	ofRectangle bounds;
	Args callbackArg;
};

} /* namespace moth */

