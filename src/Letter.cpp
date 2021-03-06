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
	fontSmall = nullptr;
	fontMedium = nullptr;
	fontLarge = nullptr;
	text = "";
	position = ofPoint(0, 0);
	width = 0;
	height = 0;

	fontSize = FONT_SMALL;

	colCurrent = _col;

	layer = LAYER_DEFAULT;

}

Letter::~Letter()
{
	// TODO Auto-generated destructor stub
}

void Letter::addChild(Symbol* _symbol)
{
	children.push_back(_symbol);
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
		fontLarge = _font;
		break;
	case FONT_MEDIUM:
		fontMedium = _font;
		break;
	case FONT_SMALL:
		fontSmall = _font;
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
		currentFont = fontLarge;
		break;
	case FONT_MEDIUM:
		currentFont = fontMedium;
		break;
	case FONT_SMALL:
		currentFont = fontSmall;
		break;

	}
	calculateSize();
}

void Letter::setLayer(LAYER _layer)
{
	layer = _layer;
	for(auto it : children)
	{
		it ->setLayer(layer);
	}
}

void Letter::display(LAYER _layer)
{
	if (layer == _layer)
	{
		ofSetColor(colCurrent);
		if (currentFont != nullptr)
		{
			currentFont->drawString(text, position.x, position.y);
		}
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

void Letter::setWidth(float _width)
{
	ofLog(OF_LOG_WARNING)
			<< "[WORD] - Setting width does nothing. Width is based on text.";
}

} /* namespace moth */

