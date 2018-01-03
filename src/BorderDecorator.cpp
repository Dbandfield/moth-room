/*
 * BorderDecorator.cpp
 *
 *  Created on: 3 Jan 2018
 *      Author: daniel
 */

#include "BorderDecorator.h"

namespace moth
{

BorderDecorator::BorderDecorator(Symbol* _decorated)
{
	decorated = _decorated;
	if (decorated != nullptr)
	{
		decorated->setColour(ofColor(0, 0, 0));
		getData();
	}
}

BorderDecorator::~BorderDecorator()
{
	if (decorated != nullptr)
	{
		delete decorated;

	}

}

void BorderDecorator::display(LAYER _layer)
{
	if (decorated != nullptr)
	{
		ofSetColor(ofColor(255, 255, 255));
		ofNoFill();
		ofDrawRectangle(position.x, position.y - decorated->getHeight(), width, height);
		decorated->display(_layer);
	}
}

std::vector<Symbol*> BorderDecorator::getChildren()
{
	if (decorated != nullptr)
	{
		return decorated->getChildren();

	}
	else
		return std::vector<Symbol*>();
}

float BorderDecorator::getHeight()
{
	if (decorated != nullptr)
	{
		return decorated->getHeight();

	}
	else
		return 0;

}

float BorderDecorator::getWidth()
{
	if (decorated != nullptr)
	{
		return decorated->getWidth();

	}
	else
		return 0;
}

ofPoint BorderDecorator::getPosition()
{
	if (decorated != nullptr)
	{
		return decorated->getPosition();

	}
	else
		return ofPoint(0, 0);
}

std::string BorderDecorator::getText()
{
	if (decorated != nullptr)
	{
		return decorated->getText();
	}
	else
		return "";
}

float BorderDecorator::getSpacing()
{
	if (decorated != nullptr)
	{
		return decorated->getSpacing();

	}
	else
		return 0;
}

void BorderDecorator::setText(char _c)
{
	if (decorated != nullptr)
	{
		decorated->setText(_c);
		getData();

	}
}

void BorderDecorator::setText(char* _c)
{
	if (decorated != nullptr)
	{
		decorated->setText(_c);
		getData();

	}
}

void BorderDecorator::setText(std::string _c)
{
	if (decorated != nullptr)
	{
		decorated->setText(_c);
		getData();

	}
}

void BorderDecorator::addChild(Symbol* _symbol)
{
	if (decorated != nullptr)
	{
		decorated->addChild(_symbol);
		getData();

	}
}

void BorderDecorator::setFont(FONT_SIZE _sz, ofTrueTypeFont *_font)
{
	if (decorated != nullptr)
	{
		decorated->setFont(_sz, _font);
		getData();

	}
}
void BorderDecorator::setFontSize(FONT_SIZE _sz)
{
	if (decorated != nullptr)
	{
		decorated->setFontSize(_sz);
		getData();

	}
}

void BorderDecorator::setPosition(ofPoint _pt)
{
	if (decorated != nullptr)
	{
		decorated->setPosition(_pt);
		getData();

	}
}

void BorderDecorator::setColour(ofColor _col)
{
	if (decorated != nullptr)
	{
		decorated->setColour(_col);

	}
}

void BorderDecorator::setWidth(float _width)
{
	if (decorated != nullptr)
	{
		decorated->setWidth(_width);
		getData();

	}
}

void BorderDecorator::getData()
{
	if (decorated != nullptr)
	{
		position = ofPoint(decorated->getPosition().x - 15,
				decorated->getPosition().y - 15);
		width = decorated->getWidth() + 30;
		height = decorated->getHeight() + 30;

	}
}

} /* namespace moth */
