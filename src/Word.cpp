/*
 * Word.cpp
 *
 *  Created on: 26 Dec 2017
 *      Author: daniel
 */

#include "Word.h"

namespace moth
{

Word::Word(ofColor _col)
{
	ofLog() << "[WORD] - Creating word";
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

Word::~Word()
{
	ofLog() << "[WORD] - Destroying word";

	for (auto i = children.begin(); i != children.end(); i++)
	{
		delete (*i);
	}

	children.clear();

}

void Word::setFont(FONT_SIZE _sz, ofTrueTypeFont *_font)
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

	for (auto i = children.begin(); i != children.end(); i++)
	{
		(*i)->setFont(_sz, _font);
	}

	calculateSize();
}

void Word::setFontSize(FONT_SIZE _sz)
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

	for (auto i = children.begin(); i != children.end(); i++)
	{
		(*i)->setFontSize(_sz);
	}

	calculateSize();
}

void Word::setText(char _c)
{
	std::string str;
	str += _c;
	setText(str);
}

void Word::setText(char* _c)
{
	std::string str = "";
	while (_c != '\0')
	{
		str += *_c;
		_c++;
	}
	setText(str);
}

void Word::setText(std::string _c)
{
//	ofLog() << "[WORD] - Setting string: " << _c;
	text = _c;
	children.clear();
	for (size_t i = 0; i < _c.size(); i++)
	{
		children.push_back(new Letter(colCurrent));
		children.back()->setText(_c[i]);
	}
	calculateSize();
}

void Word::display()
{
	for (auto i = children.begin(); i != children.end(); i++)
	{
		(*i)->display();
	}
}

std::vector<Symbol*> Word::getChildren()
{
	return children;
}

float Word::getHeight()
{
	return height;
}

float Word::getWidth()
{
	return width;
}

ofPoint Word::getPosition()
{
	return position;
}

std::string Word::getText()
{
	return text;
}

float Word::getSpacing()
{
	if (currentFont != nullptr)
	{
		return currentFont->stringWidth("p");
	}
	else
	{
		return 0;
	}
}

void Word::setColour(ofColor _col)
{
	colCurrent = _col;
	for (auto i = children.begin(); i != children.end(); i++)
	{
		(*i)->setColour(_col);
	}
}

void Word::setPosition(ofPoint _pt)
{
	//ofLog() << "[WORD] - set position to " << _pt;

	position = _pt;
	float xAdj = 0;
	for (auto i = children.begin(); i != children.end(); i++)
	{
		ofPoint pos = position;
		pos.x += xAdj;
		(*i)->setPosition(pos);
		xAdj += (*i)->getWidth() + (*i)->getSpacing();
	}
}

void Word::calculateSize()
{

	if (currentFont != nullptr)
	{
		width = 0;
		float highest = 0;
		for (auto i = children.begin(); i != children.end(); i++)
		{
			width += (*i)->getWidth();
			width += (*i)->getSpacing();
			if ((*i)->getHeight() > highest)
				highest = (*i)->getHeight();
		}

		height = highest;
	}

	//ofLog() << "[WORD] - calculate size. Width is: " << width;
}

} /* namespace moth */
