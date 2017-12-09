/*
 * TextFrame.cpp
 *
 *  Created on: 2 Dec 2017
 *      Author: daniel
 */

#include "TextFrame.h"

namespace moth
{

TextFrame::TextFrame(float _width, float _height, ofPoint _position,
		bool _isOption):isOption(true), fontLarge(0), fontMedium(0), fontSmall(0)
{
	ofLog(OF_LOG_VERBOSE) << "[TextFrame] Setup";

	bool isOption = _isOption;

	if (isOption)
	{
		ofLog(OF_LOG_VERBOSE) << "[TextFrame] Text Frame can be clicked";

		opt = new Option();
	}
	else
	{
		ofLog(OF_LOG_VERBOSE) << "[TextFrame] Text Frame Can Not be Clicked";

		opt = nullptr;
	}



	position = _position;
	adjustedPosition = position;
	width = _width;
	height = _height;
	marginLeft = marginTop = marginRight = marginBottom = 32;
	letterSpacing = 4;

	colSelected.setHsb(240, 120, 255);
	colNotSelected.setHsb(0, 0, 180);
	colStatic.setHsb(0, 0, 200);
	colCurrent = colStatic;
}

TextFrame::~TextFrame()
{
}

void TextFrame::setSelected(bool _sel)
{
	if(_sel)
	{
		colCurrent = colSelected;

	}
	else
	{
		colCurrent = colNotSelected;
	}
	for(size_t i = 0; i < symbols.size(); i ++)
	{
		symbols[i]->setColour(colCurrent);
	}
}

void TextFrame::onSelect()
{
	ofLog(OF_LOG_VERBOSE) << "[TextFrame] Selected";

	if(opt != nullptr)
	{
		opt->onSelect();
	}
	else
	{
		ofLog(OF_LOG_ERROR) << "[ERROR][TextFrame] Tried to access option on non-option text frame";
	}

}

void TextFrame::setCallback(GameControl *_gameControl,
		void (GameControl::*_f)(unsigned int), unsigned int _arg)
{
	if (isOption)
	{
		opt->setCallback(_gameControl, _f, _arg);
	}
	else
	{
		ofLog(OF_LOG_ERROR)
				<< "[TextFrame] tried to set callback of textframe not set as option.";
	}
}

void TextFrame::setPosition(float _x, float _y)
{
	position = ofPoint(_x, _y);
	recalculatePositions();
}
void TextFrame::setWidth(float _w)
{
	width = _w;
	recalculatePositions();
}
void TextFrame::setHeight(float _h)
{
	height = _h;
	recalculatePositions();
}

float TextFrame::getHeight()
{
	return height;
}

void TextFrame::display()
{
	for (size_t i = 0; i < symbols.size(); i++)
	{
		symbols[i]->display();
	}
}

void TextFrame::setText(std::string _str)
{
	ofLog(OF_LOG_VERBOSE) << "[TextFrame] Setting text: " << _str;

	symbols.clear();
	for (size_t i = 0; i < _str.size(); i++)
	{
		char c = _str[i];
		symbols.push_back(new Letter(colStatic));
		symbols.back()->setCharacter(c);

	}
	if(fontLarge != nullptr) setFont(FONT_LARGE, fontLarge);

	if(fontMedium != nullptr) setFont(FONT_MEDIUM, fontMedium);

	if(fontSmall != nullptr) setFont(FONT_SMALL, fontSmall);

	recalculatePositions();
}

void TextFrame::setFont(FONT_SIZE _sz, ofTrueTypeFont *_f)
{
	ofLog(OF_LOG_VERBOSE) << "[TextFrame] Setting Font";

	for (size_t i = 0; i < symbols.size(); i++)
	{
		symbols[i]->setFont(_sz, _f);
	}


	switch(_sz)
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

	recalculatePositions();
}

void TextFrame::setFontSize(FONT_SIZE _sz)
{
	ofLog(OF_LOG_VERBOSE) << "[TextFrame] Setting Font Size";
	for (size_t i = 0; i < symbols.size(); i++)
	{
		symbols[i]->setFontSize(_sz);
	}

	recalculatePositions();
}

void TextFrame::recalculatePositions()
{

	adjustedPosition = position;
	float letterHeight = 0;
	height = 0;
	float innerWidth = width - (marginLeft + marginRight);
	if (symbols.size() > 0)
	{
		adjustedPosition.y += symbols[0]->getHeight() * LINE_HEIGHT_ADJUST;
		letterHeight = symbols[0]->getHeight() * LINE_HEIGHT_ADJUST;
		letterSpacing = symbols[0]->getSpacing();
	}

	ofPoint thisPos = adjustedPosition;
	thisPos.x += marginLeft;
	thisPos.y += marginTop;

	float w = 0;
	size_t start = 0;
	bool lineBeginning = true;

	for (size_t i = 0; i < symbols.size(); i++)
	{

		w += (symbols[i]->getWidth() * 1.2);// + letterSpacing;
		if (w >= innerWidth)
		{
			w = 0;

			size_t ins = i;
			for (size_t j = i; j > start; j--)
			{
				if (symbols[j]->getText() == " ")
				{
					ins = std::min(j + 1, symbols.size() -1); // make sure doesnt go beyind bounds
					break;
				}
			}

			i = ins;
			thisPos.y += letterHeight;
			height += letterHeight;
			thisPos.x = adjustedPosition.x + marginLeft;

			start = i;
			lineBeginning = true;

		}

		if (!lineBeginning)
		{
			float adj = symbols[i - 1]->getWidth() + letterSpacing;
			thisPos.x += adj;
		}
		else
		{
			lineBeginning = false;
		}

		symbols[i]->setPosition(thisPos);


	}
	height = height + letterHeight + marginTop + marginBottom;




}

} /* namespace moth */
