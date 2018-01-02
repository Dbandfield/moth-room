/*
 * TextContainer.cpp
 *
 *  Created on: 6 Dec 2017
 *      Author: daniel
 */

#include "TextContainer.h"

namespace moth
{

TextContainer::TextContainer()
{
}

TextContainer::~TextContainer()
{
	for (auto i = children.begin(); i != children.end(); i++)
	{
		delete (*i);
	}

	children.clear();
}

void TextContainer::addChild(Symbol *_symbol)
{
	children.push_back(_symbol);
}

void TextContainer::display()
{
	for (auto i = children.begin(); i != children.end(); i++)
	{
		(*i)->display();
	}
}

void TextContainer::setText(char _c)
{
	std::string str = "";
	str += _c;
	setText(str);
}

void TextContainer::setText(char* _c)
{
	std::string str = "";
	while (*_c != '\0')
	{
		str += *_c;
		_c++;
	}
	setText(str);
}

void TextContainer::setText(std::string _str)
{
	TextFrame* frame = new TextFrame(width, height, position, false, false);
	frame->setText(_str);
	children.push_back(frame);
}

void TextContainer::setFont(FONT_SIZE _sz,
		ofTrueTypeFont *_font)
{
	for(auto i : children)
	{
		i->setFont(_sz, _font);
	}
}

void TextContainer::setFontSize(FONT_SIZE _sz)
{
	for(auto i : children)
	{
		i->setFontSize(_sz);
	}
}

float TextContainer::getHeight()
{
	float h = 0;
	for (auto i : children)
	{
		h += i->getHeight();
	}

	return h;

}

void TextContainer::setPosition(float _x, float _y)
{
	position = ofPoint(_x, _y);
	for (auto i : children)
	{
		i->setPosition(position);
		position.y += i->getHeight() / 2;
	}
}

void TextContainer::setWidth(float _w)
{
	width = _w;
	for (auto i : children)
	{
		TextFrame *frame = static_cast<TextFrame*>(i);
		frame->setWidth(width);
	}
}

float TextContainer::getWidth()
{
	return width;
}

ofPoint TextContainer::getPosition()
{
	return position;
}

std::string TextContainer::getText()
{
	std::string cat = "";

	for(auto i : children)
	{
		cat += i->getText();
		cat += '\n';
	}

	return cat;
}

float TextContainer::getSpacing()
{
	return 0.f;
}

void TextContainer::setColour(ofColor _col)
{
	colCurrent = _col;

	for(auto i : children)
	{
		i->setColour(colCurrent);
	}
}

std::vector<Symbol*> TextContainer::getChildren()
{
	return children;
}

void TextContainer::setPosition(ofPoint _pt)
{
	position = _pt;
}



} /* namespace moth */
