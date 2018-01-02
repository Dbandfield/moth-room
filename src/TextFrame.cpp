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
		bool _isOption, bool _isSecret)

{
	ofLog(OF_LOG_VERBOSE) << "[TextFrame] Setup";

	fontSmall = nullptr;
	fontMedium = nullptr;
	fontLarge = nullptr;

	isOption = _isOption;
	isSecret = _isSecret;

	if (isOption)
	{
		opt = new Option();
	}
	else
	{
		opt = nullptr;
	}

	position = _position;
	adjustedPosition = position;
	width = _width;
	height = _height;
	marginLeft = marginTop = marginRight = marginBottom = 64;
	letterSpacing = 4;

	selectedMod = 100;
	colStatic.setHsb(0, 0, 150);
	colIsSecret.setHsb(40, 200, 200);

	colBase = isSecret ? colIsSecret : colStatic;
	colCurrent = colBase;

}

TextFrame::~TextFrame()
{
	for (auto i = children.begin(); i != children.end(); i++)
	{
		delete (*i);
	}
}

void TextFrame::setIsSecret(bool _isSecret)
{
	ofLog() << "IS SECRET!";
	isSecret = _isSecret;

	colBase = isSecret ? colIsSecret : colStatic;

	colCurrent = colBase;

	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->setColour(colCurrent);
	}
}

void TextFrame::setSelected(bool _sel)
{
	if (_sel)
	{
		float h, s, b;
		colBase.getHsb(h, s, b);
		b = std::min(255.f, float(b + selectedMod));
		colCurrent.setHsb(h, s, b);
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

void TextFrame::setMargin(MARGIN _mgn, float _amt)
{
	switch (_mgn)
	{
	case MARGIN_TOP:
		marginTop = _amt;
		break;
	case MARGIN_RIGHT:
		marginRight = _amt;
		break;
	case MARGIN_BOTTOM:
		marginBottom = _amt;
		break;
	case MARGIN_LEFT:
		marginLeft = _amt;
		break;

	}
}

void TextFrame::onSelect()
{
	ofLog(OF_LOG_VERBOSE) << "[TextFrame] Selected";

	if (opt != nullptr)
	{
		opt->onSelect();
	}
	else
	{
		ofLog(OF_LOG_ERROR)
				<< "[ERROR][TextFrame] Tried to access option on non-option text frame";
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

void TextFrame::setPosition(ofPoint _pt)
{
	position = _pt;
	recalculatePositions();
}
void TextFrame::setWidth(float _w)
{
	width = _w;
	recalculatePositions();
}

float TextFrame::getHeight()
{
	return height;
}

void TextFrame::display()
{
	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->display();
	}
//
//	ofNoFill();
//	ofSetColor(ofColor(255, 0, 0));
//	ofDrawRectangle(position.x, position.y, width, height);
}

std::vector<std::string> TextFrame::split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		std::istringstream tokenStream2(token);
		std::string token2;
		size_t i = 0;

		while (std::getline(tokenStream2, token2, '\n'))
		{
			if (i)
			{
				ofLog() << "Pushing back new line " << i;
				tokens.push_back("\n");
			}

			tokens.push_back(token2);

			i++;
		}
	}
	return tokens;
}

void TextFrame::setText(char _c)
{
	std::string str;
	str += _c;
	setText(str);
}

void TextFrame::setText(char* _c)
{
	std::string str = "";
	while (*_c != '\0')
	{
		str += *_c;
		_c++;
	}
	setText(str);
}

void TextFrame::setText(std::string _str)
{
	ofLog(OF_LOG_VERBOSE) << "[TextFrame] Setting text: " << _str;

	children.clear();

	auto wrds = split(_str, ' ');

	for (size_t i = 0; i < wrds.size(); i++)
	{
		//ofLog() << "[TEXT_FRAME] - Split word is: " << wrds[i];
		children.push_back(new Word(colStatic));
		children.back()->setText(wrds[i]);
	}

	if (fontLarge != nullptr)
		setFont(FONT_LARGE, fontLarge);

	if (fontMedium != nullptr)
		setFont(FONT_MEDIUM, fontMedium);

	if (fontSmall != nullptr)
		setFont(FONT_SMALL, fontSmall);

	recalculatePositions();
}

void TextFrame::setColour(ofColor _col)
{
	colCurrent = _col;
}

void TextFrame::setFont(FONT_SIZE _sz, ofTrueTypeFont *_f)
{
	ofLog(OF_LOG_VERBOSE) << "[TextFrame] Setting Font";

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

	recalculatePositions();
}

void TextFrame::setFontSize(FONT_SIZE _sz)
{
	ofLog(OF_LOG_VERBOSE) << "[TextFrame] Setting Font Size";
	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->setFontSize(_sz);
	}

	recalculatePositions();
}

void TextFrame::recalculatePositions()
{
	adjustedPosition = position;
	float letterHeight = 0;
	height = 0;
	float innerWidth = width - (marginLeft + marginRight);
	if (children.size() > 0)
	{
		adjustedPosition.y += children[0]->getHeight() * LINE_HEIGHT_ADJUST;
		letterHeight = children[0]->getHeight() * LINE_HEIGHT_ADJUST;
		letterSpacing = children[0]->getSpacing();
	}

	ofPoint thisPos = adjustedPosition;
	thisPos.x += marginLeft;
	thisPos.y += marginTop;

	float w = 0;
	size_t start = 0;
	bool lineBeginning = true;

	for (int i = 0; i < (int) children.size(); i++)
	{
		ofLog() << "Symbol is: " << children[i]->getText();
		bool newLine = children[i]->getText() == "\n";
		bool invisible = children[i]->getWidth() <= 0;

		if (newLine)
		{
			ofLog() << "is newl ine";
		}

		w += (children[i]->getWidth() + letterSpacing); // + letterSpacing;
		if (w >= innerWidth || newLine)
		{
			w = invisible ? 0 : children[i]->getWidth() * 1.2;

			size_t ins = i;

			if (!newLine)
			{
				for (size_t j = i; j > start; j--)
				{
					if (children[j]->getText() == " ")
					{
						ins = std::min(j + 1, children.size() - 1); // make sure doesnt go beyond bounds
						break;
					}
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
			if (children[i - 1]->getText() != "\n")
			{
				float adj = children[i - 1]->getWidth() + letterSpacing;
				thisPos.x += adj;
			}
		}
		else
		{
			lineBeginning = false;
		}

		children[i]->setPosition(thisPos);

	}
	height = height + letterHeight + marginTop + marginBottom;

}

float TextFrame::getWidth()
{
	return width;
}

ofPoint TextFrame::getPosition()
{
	return position;
}

std::string TextFrame::getText()
{
	return text;
}

float TextFrame::getSpacing()
{
	return 0.f;
}

void TextFrame::calculateSize()
{

}

void TextFrame::addChild(Symbol* _symbol)
{
	children.push_back(_symbol);
}

} /* namespace moth */
