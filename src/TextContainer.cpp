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

void TextContainer::setIsSecret(unsigned int _id, bool _isSecret)
{
	if (_id < frames.size())
	{
		frames[_id]->setIsSecret(_isSecret);
	}
	else
	{
		ofLog(OF_LOG_ERROR)
				<< "[ERROR][TextContainer] Choose an index which actually exists please";
	}
}

void TextContainer::setMargin(unsigned int _id, MARGIN _mgn, float _amt)
{
	if (_id < frames.size())
	{
		frames[_id]->setMargin(_mgn, _amt);
	}
	else
	{
		ofLog(OF_LOG_ERROR)
				<< "[ERROR][TextContainer] Choose an index which actually exists please";
	}
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
		void (GameControl::*_f)(unsigned int), unsigned int _arg)
{
	if (_ID < frames.size())
	{
		frames[_ID]->setCallback(_gameControl, _f, _arg);
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
		(*i)->setPosition(ofPoint(x, y));
		y += (*i)->getHeight() / 2;
	}
}

void TextContainer::setWidth(float _w)
{
	for (auto i = frames.begin(); i != frames.end(); i++)
	{
		(*i)->setWidth(_w);
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
			ndx++;
		}
		ofLog(OF_LOG_VERBOSE) << "[Text Container] not Below 0 " << selected;

		return SELECTED_NO_CHANGE;
	}

}
SELECTED_BOUNDS TextContainer::incrementSelected()
{
	ofLog(OF_LOG_VERBOSE) << "[Text Container] incrementing Selected ";

	if (selected == frames.size() - 1)
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
			ndx++;
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
			ndx++;
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

std::vector<Symbol*> TextContainer::getSymbols()
{
	std::vector<Symbol*> sym;
	for (auto it = frames.begin(); it != frames.end(); it++)
	{
		std::vector<Symbol*> frameSym = (*it)->getChildren();
		sym.insert(sym.end(), frameSym.begin(), frameSym.end());
	}

	return sym;
}

} /* namespace moth */
