/*
 * MapText.cpp
 *
 *  Created on: 26 Jan 2018
 *      Author: daniel
 */

#include "MapText.h"
#include "AudioPlayer.h"

namespace moth
{

MapText::MapText(unsigned int _locId, float _width, float _height, ofPoint _position,
		AudioPlayer* _player, Symbol*_label, bool _option) :
		TextFrame(_width, _height, _position, _player, _option)

{
	label = _label;
	id = _locId;
}

MapText::~MapText()
{
	// TODO Auto-generated destructor stub
}

void MapText::display(LAYER _layer)
{
	ofSetColor(255, 255, 255);
	if (selected)
	{
		ofDrawEllipse(position.x, position.y,
				sin(ofGetElapsedTimeMillis()) * 20,
				sin(ofGetElapsedTimeMillis()) * 20);
	}
	ofDrawEllipse(position.x, position.y, 10, 10);
}

void MapText::setSelected(bool _sel)
{
	selected = _sel;
	if (_sel)
	{
		float h, s, b;
		colBase.getHsb(h, s, b);
		b = std::min(255.f, float(b + selectedMod));
		colCurrent.setHsb(h, s, b);
		label->setText(text);
	}
	else
	{
		colCurrent = colBase;
	}

	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->setColour(colCurrent);
	}
}

float MapText::getPropX()
{
	return propX;

}

float MapText::getPropY()
{
	return propY;
}

void MapText::setPropPos(float _x, float _y)
{
	propX = _x;
	propY = _y;
}

} /* namespace moth */

