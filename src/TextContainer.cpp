/*
 * TextContainer.cpp
 *
 *  Created on: 6 Dec 2017
 *      Author: daniel
 */

#include "TextContainer.h"
#include "GameControl.h"
#include "BorderDecorator.h"
#include "TextFrame.h"

namespace moth
{

TextContainer::TextContainer(FLOW _flow)
{
	flow = _flow;

	layer = LAYER_DEFAULT;

	marginLeft = 0;
	marginRight = 0;
	marginTop = 0;
	marginBottom = 0;
}

TextContainer::~TextContainer()
{
	for (auto i = children.begin(); i != children.end(); i++)
	{
		delete (*i);
	}

	children.clear();
}

void TextContainer::setBackground()
{
	std::vector<Symbol*> tmpVec;
	for (auto it : children)
	{
		auto tmpIt = it;
		BackgroundDecorator* bg = new BackgroundDecorator(tmpIt);
		BorderDecorator* bd = new BorderDecorator(bg);
		bd->setLayer(layer);
		tmpVec.push_back(bd);
	}

	children = tmpVec;
}

void TextContainer::setLayer(LAYER _layer)
{
	layer = _layer;
	for (auto it : children)
	{
		it->setLayer(layer);
	}
}

void TextContainer::addChild(Symbol *_symbol)
{
	children.push_back(_symbol);
}

void TextContainer::display(LAYER _layer)
{
	for (auto i = children.begin(); i != children.end(); i++)
	{
		(*i)->display(_layer);
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
	TextFrame* frame = new TextFrame(width - (marginLeft + marginRight),
			height - (marginTop + marginBottom),
			ofPoint(position.x + marginLeft, position.y + marginTop), nullptr, false,
			false);
	frame->setText(_str);
	children.push_back(frame);
}

void TextContainer::setFont(FONT_SIZE _sz, ofTrueTypeFont *_font)
{
	for (auto i : children)
	{
		i->setFont(_sz, _font);
	}
}

void TextContainer::setFontSize(FONT_SIZE _sz)
{
	for (auto i : children)
	{
		i->setFontSize(_sz);
	}
}

float TextContainer::getHeight()
{
	float h = 0;
	h += marginTop;
	for (auto i : children)
	{
		h += i->getHeight();
	}
	h += marginBottom;

	return h;
}

void TextContainer::setPosition(float _x, float _y)
{
	setPosition(ofPoint(_x, _y));
}

void TextContainer::setPosition(ofPoint _pt)
{
	position = ofPoint(_pt.x, _pt.y);
	ofPoint childPos = position;
	childPos.x += marginLeft;
	childPos.y += marginTop;

	for (auto i : children)
	{
		i->setPosition(childPos);
		switch (flow)
		{
		case FLOW_VERTICAL:
			childPos.y += i->getHeight();

			break;
		case FLOW_HORIZONTAL:
			childPos.x += i->getWidth() + i->getSpacing();
			;

			break;
		}
	}
}

void TextContainer::setWidth(float _w)
{
	width = _w;
	for (auto it : children)
	{
		TextFrame *frame = static_cast<TextFrame*>(it);

		if (flow == FLOW_HORIZONTAL)
		{
			frame->setWidth(
					(width - (marginLeft + marginRight)) / children.size());
		}
		else
		{
			frame->setWidth(
					(width - (marginLeft + marginRight)));
		}
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

	for (auto i : children)
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

	for (auto i : children)
	{
		i->setColour(colCurrent);
	}
}

void TextContainer::setMargin(MARGIN _mgn, float _amt)
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

std::vector<Symbol*> TextContainer::getChildren()
{
	return children;
}

} /* namespace moth */
