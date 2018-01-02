/*
 * Level.cpp
 *
 *  Created on: 30 Dec 2017
 *      Author: daniel
 */

#include "Level.h"

namespace moth
{

Level::Level()
{

}

Level::~Level()
{
	for(auto i = children.begin(); i != children.end(); i ++)
	{
		delete (*i);
	}
}

void Level::display()
{
	ofSetColor(colCurrent);
	ofNoFill();
	ofDrawRectangle(position.x, position.y, width, height);
}

std::vector<Symbol*> Level::getChildren()
{
	return children;
}

float Level::getHeight()
{
	return height;
}

float Level::getWidth()
{
	return width;
}

ofPoint Level::getPosition()
{
	return position;
}

std::string Level::getText()
{
	return text;
}

float Level::getSpacing()
{
	return 0;
}

void Level::setText(char _c)
{
	std::string str = "" + _c;
	setText(str);
}

void Level::setText(char* _c)
{
	std::string str;

	while(*_c != '\0')
	{
		str += *_c;
		_c ++;
	}

	setText(str);
}

void Level::setText(std::string _c)
{
	text = _c;
}

void Level::setFont(FONT_SIZE _sz, ofTrueTypeFont *_f)
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

void Level::setFontSize(FONT_SIZE _sz)
{
	ofLog(OF_LOG_VERBOSE) << "[TextFrame] Setting Font Size";
	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->setFontSize(_sz);
	}
}

void Level::setPosition(ofPoint _pt)
{
	position = _pt;
}

void Level::setColour(ofColor _col)
{
	colCurrent = _col;
}

void Level::setWidth(float _width)
{
	width = _width;
}

void Level::setHeight(float _height)
{
	height = _height;
}

void Level::calculateSize()
{

}

} /* namespace moth */
