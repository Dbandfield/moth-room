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
	f = nullptr;;

	m_audioPlayer = nullptr;

}

Option::~Option()
{
}

void Option::setAudioPlayer(AudioPlayer* _player)
{
	m_audioPlayer = _player;
}


void Option::onSelect()
{
	ofLog(OF_LOG_VERBOSE) << "[Options] Selected";

	((*gameControl).*f)(callbackArg);
	if(m_audioPlayer) m_audioPlayer->play(AUDIO_BUTTON);
}

void Option::setCallback(GameControl *_gameControl, void (GameControl::*_f)(Args), Args _arg)
{
	ofLog(OF_LOG_VERBOSE) << "[Option] Setting Callback";

	f = _f;
	gameControl = _gameControl;
	callbackArg = _arg;
}

} /* namespace moth */
