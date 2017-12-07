/*
 * Option.cpp
 *
 *  Created on: 2 Dec 2017
 *      Author: daniel
 */

#include "Option.h"

namespace moth
{

Option::Option()
{
	ofLog(OF_LOG_VERBOSE) << "[Option] Setup";

	gameControl = nullptr;
	f = 0;
}

Option::~Option()
{
}

void Option::onSelect()
{
	ofLog(OF_LOG_VERBOSE) << "[Options] Selected";

	((*gameControl).*f)();
}

void Option::setCallback(GameControl *_gameControl, void (GameControl::*_f)())
{
	ofLog(OF_LOG_VERBOSE) << "[Option] Setting Callback";

	f = _f;
	gameControl = _gameControl;
}

} /* namespace moth */
