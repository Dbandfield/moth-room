#pragma once

#include <ofMain.h>

#include "TextFrame.h"

namespace moth
{

class AudioPlayer;

class MapText: public TextFrame
{
public:
	MapText(float _width, float _height, ofPoint _position,
			AudioPlayer* _player, Symbol* _label,bool _option);
	virtual ~MapText();

	void display(LAYER _layer);

	float getPropX();
	float getPropY();

	void setPropPos(float _x, float _y);

	void setSelected(bool _isSel);

protected:

	Symbol* label;

	float propX;
	float propY;
};

} /* namespace VO */
