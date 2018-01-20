/*
 * AudioPlayer.cpp
 *
 *  Created on: 16 Jan 2018
 *      Author: daniel
 */

#include "AudioPlayer.h"

namespace moth
{

AudioPlayer::AudioPlayer()
{

}

AudioPlayer::~AudioPlayer()
{
}

void AudioPlayer::setAudio(std::map<AUDIO, ofSoundPlayer*> _audio)
{
	m_players = _audio;
}

void AudioPlayer::play(AUDIO _player)
{
	ofLog() <<"PLAYING";
	m_players[_player]->play();
}

} /* namespace VO */
