#pragma once

#include <ofMain.h>

#include "GameControl.h"
#include "AudioPlayer.h"

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

	void setAudioPlayer(AudioPlayer* _player);

protected:

	GameControl *gameControl;
	AudioPlayer *m_audioPlayer;
	void (GameControl::*f)(Args);
	ofRectangle bounds;
	Args callbackArg;
};

} /* namespace moth */

