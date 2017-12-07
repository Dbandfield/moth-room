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

	void setCallback(GameControl *_gameControl, void(GameControl::*_f)());
	void onSelect();

protected:

	GameControl *gameControl;
	void (GameControl::*f)();
	ofRectangle bounds;
};

} /* namespace moth */

