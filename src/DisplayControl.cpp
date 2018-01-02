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

std::vector<Symbol*> DisplayControl::getSymbols()
{
	std::vector<Symbol*> sym;
	for (auto i : containers)
	{
		std::vector<Symbol*> frameSym = i.second->getChildren();
		sym.insert(sym.end(), frameSym.begin(), frameSym.end());
	}

	return sym;
}

void DisplayControl::display()
{
	ofBackground(backgroundColour);
	ofSetColor(textColour);

	for (auto i : containers)
	{
		i.second->display();
	}

}

void DisplayControl::setFont(FONT_SIZE _sz, ofTrueTypeFont *_f)
{
	ofLog(OF_LOG_VERBOSE) << "[Display Control] Setting Font";

	for (auto i : containers)
	{
		ofLog(OF_LOG_VERBOSE) << "[Display Control] Setting Font txt ";

		i.second->setFont(_sz, _f);
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

		pcTrack += pc;

		if (pcTrack > 1.)
		{
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

		auto it = containers.find(i.first);
		if (it != containers.end())
		{
			if (it->second->getHeight() > h)
				h = it->second->getHeight();

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

	for (auto i : containers)
	{
		i.second->setPosition(layout[i.first].rect.x, layout[i.first].rect.y);
		i.second->setWidth(layout[i.first].rect.width);
	}

}

void DisplayControl::clearLayout()
{
	layout.clear();
	layout.insert(
			std::pair<unsigned int, Cell>(0,
					Cell(0, 0, 100, 0, 0, ofGetWidth(), ofGetHeight())));

}

void DisplayControl::clearContent()
{
	ofLog(OF_LOG_VERBOSE) << "[Display Control] Clearing options";
	for (auto i : containers)
	{
		delete i.second;
	}

	containers.clear();
	options.clear();

	readjustHeights();
}

void DisplayControl::addText(unsigned int _p, std::string _str, FONT_SIZE _sz)
{
	ofLog(OF_LOG_VERBOSE) << "[Display Control] Adding Text " << _str;

	ofPoint pt = ofPoint();
	pt.x = layout[_p].rect.x;
	pt.y = layout[_p].rect.y;

	if (containers.find(_p) == containers.end())
	{

		containers.insert(
				std::pair<unsigned int, TextContainer*>(_p,
						new TextContainer()));

	}

	TextFrame* frame = new TextFrame(40, 40, pt, false);

	frame->setText(_str);
	frame->setFontSize(_sz);
	frame->setMargin(MARGIN_TOP, 64);
	frame->setMargin(MARGIN_RIGHT, 64);
	frame->setMargin(MARGIN_LEFT, 64);
	frame->setMargin(MARGIN_BOTTOM, 0);

	containers[_p]->addChild(frame);

	if (fontLarge != nullptr)
		setFont(FONT_LARGE, fontLarge);
	if (fontMedium != nullptr)
		setFont(FONT_MEDIUM, fontMedium);
	if (fontSmall != nullptr)
		setFont(FONT_SMALL, fontSmall);

	readjustHeights();
}

void DisplayControl::addOption(unsigned int _p, std::string _str,
		void (GameControl::*_f)(unsigned int), unsigned int _arg, FONT_SIZE _sz,
		bool _isSecret)
{

	ofLog(OF_LOG_VERBOSE) << "[Display Control] Adding Text " << _str;

	ofPoint pt = ofPoint();
	pt.x = layout[_p].rect.x;
	pt.y = layout[_p].rect.y;

	if (containers.find(_p) == containers.end())
	{

		containers.insert(
				std::pair<unsigned int, TextContainer*>(_p,
						new TextContainer()));

	}

	TextFrame* frame = new TextFrame(40, 40, pt, true, _isSecret);

	frame->setText(_str);
	frame->setFontSize(_sz);
	frame->setMargin(MARGIN_TOP, 64);
	frame->setMargin(MARGIN_RIGHT, 64);
	frame->setMargin(MARGIN_LEFT, 64);
	frame->setMargin(MARGIN_BOTTOM, 0);
	frame->setCallback(gameControl, _f, _arg);

	options.push_back(frame);

	for(size_t i = 0; i < options.size(); i ++)
	{
		options[i]->setSelected[i == selected];
	}

	containers[_p]->addChild(frame);

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
		options[selected]->onSelect();
	}
}

void DisplayControl::onArrow(int _key)
{
	ofLog(OF_LOG_VERBOSE) << "[DisplayControl] Arrow Pressed. Selected is: "
			<< selected;

	switch (_key)
	{
	case OF_KEY_UP:
		ofLog(OF_LOG_VERBOSE) << "[DisplayControl] Arrow Pressed up";

		selected--;
		if (selected < 0)
		{
			selected = options.size() - 1;
		}

		for(size_t i = 0; i < options.size(); i ++)
		{
			options[i]->setSelected(i == selected);
		}

		break;

	case OF_KEY_DOWN:
		ofLog(OF_LOG_VERBOSE) << "[DisplayControl] Arrow down Pressed";

		selected++;
		if (selected >= options.size())
		{
			selected = 0;
		}

		for(size_t i = 0; i < options.size(); i ++)
		{
			options[i]->setSelected(i == selected);
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
