#pragma once

#include <map>
#include <string>

#include <ofMain.h>

#include "enums.h"

namespace moth
{

class AudioPlayer
{
public:
	AudioPlayer();
	virtual ~AudioPlayer();

	void setAudio(std::map<AUDIO, ofSoundPlayer*> _audio);

	void play(AUDIO _which);

protected:

	std::map<AUDIO, ofSoundPlayer*> m_players;

};

} /* namespace VO */
