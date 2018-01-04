/*
 * BackgroundDecorator.cpp
 *
 *  Created on: 3 Jan 2018
 *      Author: daniel
 */

#include "BackgroundDecorator.h"

namespace moth
{

BackgroundDecorator::BackgroundDecorator(Symbol* _decorated)
{
	decorated = _decorated;
	if (decorated != nullptr)
	{
		decorated->setColour(ofColor(0, 0, 0));
		getData();
	}

	layer = LAYER_DEFAULT;
}

BackgroundDecorator::~BackgroundDecorator()
{
	if (decorated != nullptr)
	{
		delete decorated;

	}

}

void BackgroundDecorator::display(LAYER _layer)
{
	if (decorated != nullptr)
	{
		if (_layer == layer)
		{
			ofFill();
			ofSetColor(ofColor(255, 255, 255));
			ofDrawRectangle(position.x, position.y - decorated->getHeight(),
					width, height);
		}
		decorated->display(_layer);
	}
}

std::vector<Symbol*> BackgroundDecorator::getChildren()
{
	if (decorated != nullptr)
	{
		return decorated->getChildren();

	}
	else
		return std::vector<Symbol*>();
}

float BackgroundDecorator::getHeight()
{
	if (decorated != nullptr)
	{
		return decorated->getHeight();

	}
	else
		return 0;

}

float BackgroundDecorator::getWidth()
{
	if (decorated != nullptr)
	{
		return decorated->getWidth();

	}
	else
		return 0;
}

ofPoint BackgroundDecorator::getPosition()
{
	if (decorated != nullptr)
	{
		return decorated->getPosition();

	}
	else
		return ofPoint(0, 0);
}

std::string BackgroundDecorator::getText()
{
	if (decorated != nullptr)
	{
		return decorated->getText();
	}
	else
		return "";
}

float BackgroundDecorator::getSpacing()
{
	if (decorated != nullptr)
	{
		return decorated->getSpacing();

	}
	else
		return 0;
}

void BackgroundDecorator::setText(char _c)
{
	if (decorated != nullptr)
	{
		decorated->setText(_c);
		getData();

	}
}

void BackgroundDecorator::setText(char* _c)
{
	if (decorated != nullptr)
	{
		decorated->setText(_c);
		getData();

	}
}

void BackgroundDecorator::setText(std::string _c)
{
	if (decorated != nullptr)
	{
		decorated->setText(_c);
		getData();

	}
}

void BackgroundDecorator::addChild(Symbol* _symbol)
{
	if (decorated != nullptr)
	{
		decorated->addChild(_symbol);
		getData();

	}
}

void BackgroundDecorator::setFont(FONT_SIZE _sz, ofTrueTypeFont *_font)
{
	if (decorated != nullptr)
	{
		decorated->setFont(_sz, _font);
		getData();

	}
}
void BackgroundDecorator::setFontSize(FONT_SIZE _sz)
{
	if (decorated != nullptr)
	{
		decorated->setFontSize(_sz);
		getData();

	}
}

void BackgroundDecorator::setPosition(ofPoint _pt)
{
	if (decorated != nullptr)
	{
		decorated->setPosition(_pt);
		getData();

	}
}

void BackgroundDecorator::setColour(ofColor _col)
{
	if (decorated != nullptr)
	{
		decorated->setColour(_col);

	}
}

void BackgroundDecorator::setWidth(float _width)
{
	if (decorated != nullptr)
	{
		decorated->setWidth(_width);
		getData();

	}
}

void BackgroundDecorator::getData()
{
	if (decorated != nullptr)
	{
		position = ofPoint(decorated->getPosition().x - 10,
				decorated->getPosition().y - 10);
		width = decorated->getWidth() + 20;
		height = decorated->getHeight() + 20;

	}
}

void BackgroundDecorator::setLayer(LAYER _layer)
{
	layer = _layer;
	for (auto it : children)
	{
		it->setLayer(layer);
	}
	decorated->setLayer(layer);

}

} /* namespace moth */
