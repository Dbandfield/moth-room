/*
 * LevelsFrame.cpp
 *
 *  Created on: 30 Dec 2017
 *      Author: daniel
 */

#include "LevelsFrame.h"

namespace moth
{

LevelsFrame::LevelsFrame()
{
	text = "";

	layer = LAYER_DEFAULT;
}

LevelsFrame::~LevelsFrame()
{
	for(auto i = children.begin(); i != children.end(); i ++)
	{
		delete (*i);
	}
}

void LevelsFrame::setLayer(LAYER _layer)
{
	layer = _layer;
	for(auto it : children)
	{
		it ->setLayer(layer);
	}
}

void LevelsFrame::display(LAYER _layer)
{
	for(auto i = children.begin(); i != children.end(); i ++)
	{
		(*i)->display(_layer);
	}
}

std::vector<Symbol*> LevelsFrame::getChildren()
{
	return children;
}

float LevelsFrame::getHeight()
{
	return height;
}

float LevelsFrame::getWidth()
{
	return width;
}

ofPoint LevelsFrame::getPosition()
{
	return position;
}

std::string LevelsFrame::getText()
{
	return text;
}

float LevelsFrame::getSpacing()
{
	return 0;
}

void LevelsFrame::setText(char _c)
{
	std::string str = "" + _c;
	setText(str);
}

void LevelsFrame::setText(char* _c)
{
	std::string str;

	while(*_c != '\0')
	{
		str += *_c;
		_c ++;
	}

	setText(str);
}

void LevelsFrame::setText(std::string _c)
{
	text = _c;
}

void LevelsFrame::setFont(FONT_SIZE _sz, ofTrueTypeFont *_f)
{
	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->setFont(_sz, _f);
	}

	switch (_sz)
	{
	case FONT_LARGE:
		fontLarge = _f;
		break;
	case FONT_MEDIUM:
		fontMedium = _f;
		break;
	case FONT_SMALL:
		fontSmall = _f;
		break;
	}
}

void LevelsFrame::setFontSize(FONT_SIZE _sz)
{
	ofLog(OF_LOG_VERBOSE) << "[TextFrame] Setting Font Size";
	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->setFontSize(_sz);
	}
}

void LevelsFrame::setPosition(ofPoint _pt)
{
	position = _pt;
}

void LevelsFrame::setColour(ofColor _col)
{
	colCurrent = _col;
}

void LevelsFrame::addChild(Symbol* _symbol)
{
	children.push_back(_symbol);
}

void LevelsFrame::setWidth(float _width)
{
	width = _width;
}

void LevelsFrame::setHeight(float _height)
{
	height = _height;
}

} /* namespace moth */
