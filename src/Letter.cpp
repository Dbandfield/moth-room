/*
 * Letter.cpp
 *
 *  Created on: 2 Dec 2017
 *      Author: daniel
 */

#include "Letter.h"

namespace moth
{

Letter::Letter(ofColor _col)
{

	currentFont = nullptr;
	smallFont = nullptr;
	mediumFont = nullptr;
	largeFont = nullptr;
	text = "";
	position = ofPoint(0, 0);
	width = 0;
	height = 0;

	fontSize = FONT_SMALL;

	colCurrent = _col;

}

Letter::~Letter()
{
	// TODO Auto-generated destructor stub
}

float Letter::getWidth()
{
	return width;
}
float Letter::getHeight()
{
	return height;
}
ofPoint Letter::getPosition()
{
	return position;
}

void Letter::setColour(ofColor _col)
{

	colCurrent = _col;
	float h, s, b;
	colCurrent.getHsb(h, s, b);
}

float Letter::getSpacing()
{
	if (currentFont != nullptr)
	{
		return currentFont->getLetterSpacing() * 6;
	}
	else
	{
		return 0;
	}
}

void Letter::setFont(FONT_SIZE _sz, ofTrueTypeFont *_font)
{
	switch (_sz)
	{
	case FONT_LARGE:
		largeFont = _font;
		break;
	case FONT_MEDIUM:
		mediumFont = _font;
		break;
	case FONT_SMALL:
		smallFont = _font;
		break;

	}
	setFontSize(fontSize);
	calculateSize();
}

void Letter::setFontSize(FONT_SIZE _sz)
{
	fontSize = _sz;
	switch (_sz)
	{
	case FONT_LARGE:
		currentFont = largeFont;
		break;
	case FONT_MEDIUM:
		currentFont = mediumFont;
		break;
	case FONT_SMALL:
		currentFont = smallFont;
		break;

	}
	calculateSize();
}

void Letter::display()
{
	ofSetColor (colCurrent);
	if (currentFont != nullptr)
	{
		currentFont->drawString(text, position.x, position.y);
	}
}

std::vector<Symbol*> Letter::getChildren()
{
	return children;
}

void Letter::setText(char _c)
{

	text = std::string();
	text += _c;
	calculateSize();
}

void Letter::setText(char* _c)
{

	text = std::string();
	text += _c[0];
	calculateSize();
}

void Letter::setText(std::string _c)
{

	text = _c.substr(0, 1);
	calculateSize();
}

void Letter::setPosition(ofPoint _pt)
{
	position = _pt;
}

void Letter::calculateSize()
{
	if (currentFont != nullptr)
	{
		if (text == " ")
		{
			width = currentFont->stringWidth("p");
			height = currentFont->stringHeight("p");
		}
		else
		{
			width = currentFont->stringWidth(text);
			height = currentFont->stringHeight(text);
		}
	}

}

} /* namespace moth */

