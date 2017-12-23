/*
 * Display.cpp
 *
 *  Created on: 2 Dec 2017
 *      Author: daniel
 */

#include "DisplayControl.h"

namespace moth
{

DisplayControl::DisplayControl() :
		selected(0), fontLarge(0), fontMedium(0), fontSmall(0)
{
	ofLog(OF_LOG_VERBOSE) << "[DisplayControl] Setup";

	gameControl = nullptr;

	backgroundColour = ofColor();
	backgroundColour.setHsb(0, 0, 30);

	textColour = ofColor();
	textColour.setHsb(0, 0, 200);

	clearLayout();

	ofAddListener(ofEvents().keyReleased, this, &DisplayControl::onKeyPressed);
}

DisplayControl::~DisplayControl()
{
	ofRemoveListener(ofEvents().keyReleased, this,
			&DisplayControl::onKeyPressed);
}

void DisplayControl::display()
{
	ofBackground(backgroundColour);
	ofSetColor(textColour);
	for (auto i = layout.begin(); i != layout.end(); i++)
	{
		/* Was for debugging layout, will delete later. */
//		ofNoFill();
//		ofDrawRectangle(i->second.rect);
//		std::stringstream ss;
//		ss << i->first;
//
//		fontLarge->drawString(ss.str(), i->second.rect.x, i->second.rect.y + 100);
	}

	for (auto i = text.begin(); i != text.end(); i++)
	{
		i->second->display();
	}

	for (auto i = options.begin(); i != options.end(); i++)
	{
		i->second->display();
	}

}

void DisplayControl::setFont(FONT_SIZE _sz, ofTrueTypeFont *_f)
{
	ofLog(OF_LOG_VERBOSE) << "[Display Control] Setting Font";
	int it = 0;
	for (auto i = text.begin(); i != text.end(); i++)
	{
		ofLog(OF_LOG_VERBOSE) << "[Display Control] Setting Font txt " << it;

		for (size_t ii = 0; ii < i->second->getSize(); ii++)
		{
			i->second->setFont(ii, _sz, _f);
		}
		it++;
	}

	for (auto i = options.begin(); i != options.end(); i++)
	{
		ofLog(OF_LOG_VERBOSE) << "[Display Control] Setting Font opt " << it;

		for (size_t ii = 0; ii < i->second->getSize(); ii++)
		{
			i->second->setFont(ii, _sz, _f);
		}

		it++;
	}

	ofLog(OF_LOG_VERBOSE) << "[Display Control] Setting personal font ";

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

	readjustHeights();

}

void DisplayControl::setLayout(std::vector<float> _layout)
{
	ofLog(OF_LOG_VERBOSE) << "[Display Control] Setting layout";
	layout.clear();
	float w = 0;
	float h = 50;
	float x = 0;
	float y = 0;
	unsigned int id = 0;
	unsigned int row = 0;
	unsigned int col = 0;
	float pcTrack = 0;

	for (size_t i = 0; i < _layout.size(); i++)
	{
		float pc = _layout[i] / 100.f;
		ofLog() << "Percent of this is " << pc;

		pcTrack += pc;

		ofLog() << "Total percent of this line is " << pcTrack;

		if (pcTrack > 1.)
		{
			ofLog() << "Time for new row " << i;
			row++;
			x = 0;
			y += h;
			col = 0;
			pcTrack = pc;
		}
		else
		{
		}

		w = ofGetWidth() * pc;
		id = i;

		layout.insert(
				std::pair<unsigned int, Cell>(id,
						Cell(row, col, pc, x, y, w, h)));

		x += w;
		col++;

	}

	readjustHeights();
}

void DisplayControl::readjustHeights()
{
	ofLog(OF_LOG_VERBOSE) << "[DisplayControl] Readjusting Heights";
	std::vector<float> rowMaxHeight;
	float h = 0;
	unsigned int thisRow = 0;
	for (auto i : layout)
	{
		if (i.second.row != thisRow)
		{
			rowMaxHeight.push_back(h);
			h = 0;
			thisRow = i.second.row;
		}

		auto it = text.find(i.first);
		if (it != text.end())
		{
			if (it->second->getHeight() > h)
				h = it->second->getHeight();
		}
		else
		{
			auto it2 = options.find(i.first);
			if (it2 != options.end())
			{
				if (it2->second->getHeight() > h)
					h = it2->second->getHeight();
			}
		}

	}

	if (layout.size() > 0)
		rowMaxHeight.push_back(h);

	thisRow = 0;
	float y = 0;

	for (auto i = layout.begin(); i != layout.end(); i++)
	{
		Cell& cell = i->second;
		if (cell.row != thisRow)
		{
			y += rowMaxHeight[thisRow];
			thisRow = cell.row;
		}
		cell.rect.setHeight(rowMaxHeight[thisRow]);
		cell.rect.setY(y);
	}

	for (auto i = text.begin(); i != text.end(); i++)
	{
		i->second->setPosition(layout[i->first].rect.x,
				layout[i->first].rect.y);
		i->second->setWidth(layout[i->first].rect.width);
		//i.second->setHeight(layout[i.first].rect.height);
	}

	for (auto i = options.begin(); i != options.end(); i++)
	{
		i->second->setPosition(layout[i->first].rect.x,
				layout[i->first].rect.y);
		i->second->setWidth(layout[i->first].rect.width);
		//i.second->setHeight(layout[i.first].rect.height);
	}

}

void DisplayControl::clearLayout()
{
	layout.clear();
	layout.insert(
			std::pair<unsigned int, Cell>(0,
					Cell(0, 0, 100, 0, 0, ofGetWidth(), ofGetHeight())));

}

void DisplayControl::clearText()
{
	ofLog(OF_LOG_VERBOSE) << "[Display Control] Clearing options";
	for (auto i = text.begin(); i != text.end(); i++)
	{
		delete i->second;
	}

	text.clear();

	readjustHeights();

}

void DisplayControl::addText(unsigned int _p, std::string _str, FONT_SIZE _sz)
{
	ofLog(OF_LOG_VERBOSE) << "[Display Control] Adding Text " << _str;

	ofPoint pt = ofPoint();
	pt.x = layout[_p].rect.x;
	pt.y = layout[_p].rect.y;

	if (text.find(_p) == text.end())
	{

		text.insert(
				std::pair<unsigned int, TextContainer*>(_p,
						new TextContainer()));
		text[_p]->addTextFrame(40, 40, pt, false);
		text[_p]->setText(text[_p]->getSize() - 1, _str);
		text[_p]->setFontSize(text[_p]->getSize() - 1, _sz);
	}
	else
	{
		text[_p]->addTextFrame(40, 40, pt, false);
		text[_p]->setText(text[_p]->getSize() - 1, _str);
		text[_p]->setFontSize(text[_p]->getSize() - 1, _sz);
	}

	text[_p]->setMargin(text[_p]->getSize() - 1, MARGIN_TOP, 64);
	text[_p]->setMargin(text[_p]->getSize() - 1, MARGIN_RIGHT, 64);
	text[_p]->setMargin(text[_p]->getSize() - 1, MARGIN_LEFT, 64);
	text[_p]->setMargin(text[_p]->getSize() - 1, MARGIN_BOTTOM, 0);

	if (fontLarge != nullptr)
		setFont(FONT_LARGE, fontLarge);
	if (fontMedium != nullptr)
		setFont(FONT_MEDIUM, fontMedium);
	if (fontSmall != nullptr)
		setFont(FONT_SMALL, fontSmall);

	readjustHeights();
}

void DisplayControl::clearOptions()
{
	ofLog(OF_LOG_VERBOSE) << "[Display Control] Clearing options";
	for (auto i = options.begin(); i != options.end(); i++)
	{
		delete i->second;
	}

	options.clear();

	readjustHeights();

}

void DisplayControl::addOption(unsigned int _p, std::string _str,
		void (GameControl::*_f)(unsigned int), unsigned int _arg, FONT_SIZE _sz)
{
	ofLog(OF_LOG_VERBOSE) << "[Display Control] Adding option " << _str;

	ofPoint pt = ofPoint();
	pt.x = layout[_p].rect.x;
	pt.y = layout[_p].rect.y;

	if (options.find(_p) == options.end())
	{

		options.insert(
				std::pair<unsigned int, TextContainer*>(_p,
						new TextContainer()));
		options[_p]->addTextFrame(40, 40, pt, true);
		options[_p]->setText(options[_p]->getSize() - 1, _str);
		options[_p]->setFontSize(options[_p]->getSize() - 1, _sz);
		options[_p]->setCallback(options[_p]->getSize() - 1, gameControl, _f,
				_arg);
	}
	else
	{
		options[_p]->addTextFrame(40, 40, pt, true);
		options[_p]->setText(options[_p]->getSize() - 1, _str);
		options[_p]->setFontSize(options[_p]->getSize() - 1, _sz);
		options[_p]->setCallback(options[_p]->getSize() - 1, gameControl, _f,
				_arg);
	}

	options[_p]->setMargin(options[_p]->getSize() - 1, MARGIN_TOP, 64);
	options[_p]->setMargin(options[_p]->getSize() - 1, MARGIN_RIGHT, 64);
	options[_p]->setMargin(options[_p]->getSize() - 1, MARGIN_LEFT, 64);
	options[_p]->setMargin(options[_p]->getSize() - 1, MARGIN_BOTTOM, 64);

	if (options.size() != 0)
	{
		options[_p]->setSelected(true, SELECTED_NO_CHANGE);
	}

	if (fontLarge != nullptr)
		setFont(FONT_LARGE, fontLarge);
	if (fontMedium != nullptr)
		setFont(FONT_MEDIUM, fontMedium);
	if (fontSmall != nullptr)
		setFont(FONT_SMALL, fontSmall);

	readjustHeights();

}

void DisplayControl::onKeyPressed(ofKeyEventArgs &_args)
{
	ofLog(OF_LOG_VERBOSE) << "[DisplayControl] Key Pressed";

	switch (_args.key)
	{
	case OF_KEY_UP:
	case OF_KEY_RIGHT:
	case OF_KEY_DOWN:
	case OF_KEY_LEFT:
		onArrow(_args.key);
		break;
	case ' ':
	case OF_KEY_RETURN:
		onSelect();
		break;
	}
}

void DisplayControl::onSelect()
{
	ofLog(OF_LOG_VERBOSE) << "[DisplayControl] Something Selected";

	if (options.size() > 0)
	{
		ofLog() << selected;
		size_t i = 0;
		for (auto it = options.begin(); it != options.end(); it++)
		{
			if (i == selected)
			{
				it->second->onSelect();
				break;
			}

			i++;
		}
	}
}

void DisplayControl::onArrow(int _key)
{
	ofLog(OF_LOG_VERBOSE) << "[DisplayControl] Arrow Pressed. Selected is: "
			<< selected;
	size_t i = 0;

	switch (_key)
	{
	case OF_KEY_UP:
		ofLog(OF_LOG_VERBOSE) << "[DisplayControl] Arrow Pressed up";

		for (auto it = options.begin(); it != options.end(); it++)
		{
			if (i == selected)
			{
				switch (it->second->decrementSelected())
				{
				case SELECTED_ABOVE:
					selected--;
					if (selected < 0)
						selected = options.size() - 1;

					size_t i2 = 0;
					for (auto it2 = options.begin(); it2 != options.end();
							it2++)
					{

						if (i2 == selected)
						{
							it2->second->setSelected(true, SELECTED_BELOW);
						}
						else
						{
							it2->second->setSelected(false, SELECTED_NO_CHANGE);
						}
						i2++;
					}
					break;
				}

				break;
			}
			i++;
		}

		break;

	case OF_KEY_DOWN:
		ofLog(OF_LOG_VERBOSE) << "[DisplayControl] Arrow down Pressed";

		i = 0;
		for (auto it = options.begin(); it != options.end(); it++)
		{
			if (i == selected)
			{
				switch (it->second->incrementSelected())
				{
				case SELECTED_BELOW:
					selected++;
					if (selected >= options.size())
						selected = 0;

					size_t i2 = 0;
					for (auto it2 = options.begin(); it2 != options.end();
							it2++)
					{

						if (i2 == selected)
						{
							it2->second->setSelected(true, SELECTED_ABOVE);
						}
						else
						{
							it2->second->setSelected(false, SELECTED_NO_CHANGE);
						}
						i2++;
					}
					break;
				}

				break;
			}
			i++;
		}

		break;
	}
}

void DisplayControl::setGameControl(GameControl *_gameControl)
{
	ofLog(OF_LOG_VERBOSE) << "[Display Control] Setting Game Control";

	gameControl = _gameControl;
}

} /* namespace moth */
