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
	text = "";
	currentFont = fontSmall = fontMedium = fontLarge = nullptr;
	barWidth = 60;
	barMaxHeight = 0;
	barPercent = 100;
	barRealHeight = barMaxHeight * (barPercent / 100.f);

	marginTop = 20;
	marginBottom = 70;
	marginLeft = 10;
	marginRight = 10;

	colCurrent = ofColor(255, 255, 255);

	layer = LAYER_DEFAULT;

	readjustDimensions();
}

Level::~Level()
{
	for (auto i = children.begin(); i != children.end(); i++)
	{
		delete (*i);
	}
}

void Level::setValue(float _value)
{
	barPercent = std::min(100.f, std::max(0.f, _value));
	barRealHeight = barMaxHeight * (barPercent / 100);
}

void Level::setLayer(LAYER _layer)
{
	layer = _layer;
	for(auto it : children)
	{
		it ->setLayer(layer);
	}
}

void Level::display(LAYER _layer)
{

	if (layer == _layer)
	{
		ofSetColor(colCurrent);

		ofNoFill();
		ofSetLineWidth(2);
		ofDrawRectangle(barPos.x, barPos.y, barWidth, barMaxHeight);
		ofFill();
		ofDrawRectangle(barPos.x + 10,
				barPos.y + 10 + (barMaxHeight - barRealHeight), barWidth - 20,
				barRealHeight - 20);

		for (auto it : children)
		{
			it->display(_layer);
		}
	}
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

	while (*_c != '\0')
	{
		str += *_c;
		_c++;
	}

	setText(str);
}

void Level::setText(std::string _c)
{
	text = _c;

	children.clear();

	for (auto it : _c)
	{
		children.push_back(new Letter(ofColor(0, 0, 0)));
		children.back()->setText(it);
	}

	readjustDimensions();
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
	ofLog(OF_LOG_VERBOSE) << "[LEVEL] Setting Font Size";
	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->setFontSize(_sz);
	}

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
}

void Level::setPosition(ofPoint _pt)
{
	position = _pt;

	readjustDimensions();
}

void Level::setColour(ofColor _col)
{
	colCurrent = _col;
}

void Level::setWidth(float _width)
{
	width = _width;

	readjustDimensions();

}

void Level::setHeight(float _height)
{
	height = _height;

	readjustDimensions();

}

void Level::addChild(Symbol* _symbol)
{

}

void Level::readjustDimensions()
{
	float x, y;
	x = position.x;
	x += width / 2;
	x -= barWidth / 2;

	y = position.y;
	y += marginTop;

	barMaxHeight = height - (marginTop + marginBottom);
	barRealHeight = barMaxHeight * (barPercent / 100);

	barPos = ofPoint(x, y);

	x = barPos.x + (barWidth / 2);
	if (children.size() > 0)
	{
		x -= children[0]->getWidth() / 2;
	}
	y = barPos.y + 32;

	float inc = barMaxHeight / ((float) children.size() + 4);
	y += inc * 2;
	for (auto it : children)
	{
		it->setPosition(ofPoint(x, y));
		y += inc;
	}
}

} /* namespace moth */
