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
	selected = 0;
}

TextContainer::~TextContainer()
{
	for (auto i = frames.begin(); i != frames.end(); i++)
	{
		delete (*i);
	}

	frames.clear();
}

void TextContainer::addTextFrame(float _width, float _height, ofPoint _position,
		bool _isOption)
{
	frames.push_back(new TextFrame(_width, _height, _position, _isOption));
}

void TextContainer::display()
{
	for (auto i = frames.begin(); i != frames.end(); i++)
	{
		(*i)->display();
	}
}

void TextContainer::setText(unsigned int _ID, std::string _str)
{
	if (_ID < frames.size())
	{
		frames[_ID]->setText(_str);
	}
	else
	{
		ofLog(OF_LOG_ERROR)
				<< "[ERROR][TextContainer] Choose an index which actually exists please";
	}
}

void TextContainer::setFont(unsigned int _ID, FONT_SIZE _sz,
		ofTrueTypeFont *_font)
{
	if (_ID < frames.size())
	{
		ofLog() << "ah";
		frames[_ID]->setFont(_sz, _font);
	}
	else
	{
		ofLog(OF_LOG_ERROR)
				<< "[ERROR][TextContainer] Choose an index which actually exists please";
	}
}

void TextContainer::setFontSize(unsigned int _ID, FONT_SIZE _sz)
{
	if (_ID < frames.size())
	{
		frames[_ID]->setFontSize(_sz);
	}
	else
	{
		ofLog(OF_LOG_ERROR)
				<< "[ERROR][TextContainer] Choose an index which actually exists please";
	}
}

void TextContainer::setCallback(unsigned int _ID, GameControl *_gameControl,
		void (GameControl::*_f)())
{
	if (_ID < frames.size())
	{
		frames[_ID]->setCallback(_gameControl, _f);
	}
	else
	{
		ofLog(OF_LOG_ERROR)
				<< "[ERROR][TextContainer] Choose an index which actually exists please";
	}
}

float TextContainer::getHeight()
{
	float h = 0;
	for (auto i = frames.begin(); i != frames.end(); i++)
	{
		h += (*i)->getHeight();
	}

	return h;

}

void TextContainer::setPosition(float _x, float _y)
{
	float x = _x;
	float y = _y;
	for (auto i = frames.begin(); i != frames.end(); i++)
	{
		(*i)->setPosition(x, y);
		y += (*i)->getHeight();
	}
}

void TextContainer::setWidth(float _w)
{
	for (auto i = frames.begin(); i != frames.end(); i++)
	{
		(*i)->setWidth(_w);
	}
}

void TextContainer::setHeight(float _h)
{
	for (auto i = frames.begin(); i != frames.end(); i++)
	{
		(*i)->setHeight(_h);
	}
}

SELECTED_BOUNDS TextContainer::decrementSelected()
{
	ofLog(OF_LOG_VERBOSE) << "[Text Container] Decrementing Selected ";

	if (selected == 0)
	{
		for (auto i = frames.begin(); i != frames.end(); i++)
		{
			(*i)->setSelected(false);
		}
		ofLog(OF_LOG_VERBOSE) << "[Text Container] Below 0 " << selected;

		return SELECTED_ABOVE;
	}
	else
	{
		selected--;
		size_t ndx = 0;
		for (auto i = frames.begin(); i != frames.end(); i++)
		{
			(*i)->setSelected(ndx == selected);
			ndx ++;
		}
		ofLog(OF_LOG_VERBOSE) << "[Text Container] not Below 0 " << selected;

		return SELECTED_NO_CHANGE;
	}


}
SELECTED_BOUNDS TextContainer::incrementSelected()
{
	ofLog(OF_LOG_VERBOSE) << "[Text Container] incrementing Selected ";


	if (selected == frames.size()-1)
	{
		for (auto i = frames.begin(); i != frames.end(); i++)
		{
			(*i)->setSelected(false);
		}
		ofLog(OF_LOG_VERBOSE) << "[Text Container] over max " << selected;

		return SELECTED_BELOW;
	}
	else
	{
		selected++;
		size_t ndx = 0;
		for (auto i = frames.begin(); i != frames.end(); i++)
		{
			(*i)->setSelected(ndx == selected);
			ndx ++;
		}
		ofLog(OF_LOG_VERBOSE) << "[Text Container] not over max " << selected;

		return SELECTED_NO_CHANGE;
	}


}

void TextContainer::setSelected(bool _sel, SELECTED_BOUNDS _bounds)
{
	ofLog(OF_LOG_VERBOSE) << "[Text Container] Set selected";

	if (_sel)
	{
		//frames[selected]->setSelected(true);
		switch (_bounds)
		{
		case SELECTED_ABOVE:
		default:
			selected = 0;
			break;
		case SELECTED_BELOW:
			selected = frames.size() - 1;
			break;
		}

		size_t ndx = 0;
		for (auto i = frames.begin(); i != frames.end(); i++)
		{
			(*i)->setSelected(ndx == selected);
			ndx ++;
		}

	}
	else
	{
		for (auto i = frames.begin(); i != frames.end(); i++)
		{
			(*i)->setSelected(false);
		}
	}
	ofLog(OF_LOG_VERBOSE) << "[Text Container] selected is " << selected;


}

void TextContainer::onSelect()
{
	ofLog(OF_LOG_VERBOSE) << "on select " << selected;

	frames[selected]->onSelect();
}

} /* namespace moth */
