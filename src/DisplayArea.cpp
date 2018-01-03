/*
 * DisplayArea.cpp
 *
 *  Created on: 2 Jan 2018
 *      Author: daniel
 */

#include "DisplayArea.h"

namespace moth
{

DisplayArea::DisplayArea()
{
	numCells = 0;
	width = 0;
	height = 0;
	index = 0;
	clearLayout();

}

DisplayArea::DisplayArea(ofPoint _pos, float _width, float _height)
{
	numCells = 0;
	position = _pos;
	width = _width;
	height = _height;
	clearLayout();
}

DisplayArea::~DisplayArea()
{
}

void DisplayArea::display(LAYER _layer)
{
	for (auto it : containers)
	{
		it.second->display();
	}
}

std::vector<Symbol*> DisplayArea::getChildren()
{
	std::vector<Symbol*> sym;
	for (auto it : containers)
	{
		sym.push_back(it.second);
	}
	return sym;
}

float DisplayArea::getHeight()
{
	return height;
}

float DisplayArea::getWidth()
{
	return width;
}

ofPoint DisplayArea::getPosition()
{
	return position;
}

std::string DisplayArea::getText()
{
	return text;
}

float DisplayArea::getSpacing()
{
	return 0;
}

void DisplayArea::setText(char _c)
{
	std::string str = "";
	str += _c;
	setText(str);
}

void DisplayArea::setText(char* _c)
{
	std::string str = "";
	while (*_c != '\0')
	{
		str += *_c;
		_c++;
	}
	setText(str);
}

void DisplayArea::setText(std::string _str)
{
	TextContainer* con = new TextContainer(FLOW_VERTICAL);
	con->setText(_str);
	containers.insert(std::pair<unsigned int, Symbol*>(index, con));

	readjustHeights();
}

void DisplayArea::addChild(Symbol* _symbol)
{
	containers.insert(std::pair<unsigned int, Symbol*>(index, _symbol));
}

void DisplayArea::setFont(FONT_SIZE _sz, ofTrueTypeFont *_font)
{

	for (auto it : containers)
	{
		it.second->setFont(_sz, _font);
	}

	switch (_sz)
	{
	case FONT_LARGE:

		fontLarge = _font;
		break;
	case FONT_MEDIUM:

		fontMedium = _font;
		break;
	case FONT_SMALL:

		fontSmall = _font;
		break;
	}

	readjustHeights();
}

void DisplayArea::setFontSize(FONT_SIZE _sz)
{
	for (auto it : containers)
	{
		it.second->setFontSize(_sz);
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

	readjustHeights();
}

void DisplayArea::setPosition(ofPoint _pt)
{
	position = _pt;
}

void DisplayArea::setColour(ofColor _col)
{
	colCurrent = _col;

	for (auto it : containers)
	{
		it.second->setColour(colCurrent);
	}
}

void DisplayArea::setLayout(std::vector<float> _layout)
{
	ofLog(OF_LOG_VERBOSE) << "[DISPLAY_AREA] - Setting layout";
	layout.clear();
	percentages = _layout;
	float w = 0;
	float h = height;
	float x = position.x;
	float y = position.y;
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
			x = position.x;
			y += h;
			col = 0;
			pcTrack = pc;
		}
		else
		{
		}

		w = width * pc;
		id = i;

		layout.insert(
				std::pair<unsigned int, Cell>(id,
						Cell(row, col, pc, x, y, w, h)));

		x += w;
		col++;

	}

	readjustHeights();
}

bool DisplayArea::setIndex(unsigned int _index)
{
	index = _index;

	auto q = containers.find(_index);
	return (q == containers.end());
}

void DisplayArea::readjustHeights()
{
	ofLog(OF_LOG_VERBOSE) << "[DISPLAY_AREA] - Readjusting Heights";
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
	float y = position.y;

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
		i.second->setPosition(
				ofPoint(layout[i.first].rect.x, layout[i.first].rect.y));
		i.second->setWidth(layout[i.first].rect.width);
	}

}

void DisplayArea::setWidth(float _width)
{
	width = _width;
	setLayout(percentages);
}

void DisplayArea::clearLayout()
{
	percentages.clear();
	layout.clear();
	layout.insert(
			std::pair<unsigned int, Cell>(0,
					Cell(0, 0, 100, position.x, position.y, width, height)));

}

TextFrame* DisplayArea::addText(unsigned int _p, std::string _str,
		FONT_SIZE _sz)
{
	ofLog(OF_LOG_VERBOSE) << "[DISPLAY_AREA] - Adding Text " << _str;

	ofPoint pt = ofPoint();
	pt.x = layout[_p].rect.x;
	pt.y = layout[_p].rect.y;

	if (containers.find(_p) == containers.end())
	{

		containers.insert(
				std::pair<unsigned int, TextContainer*>(_p,
						new TextContainer(FLOW_VERTICAL)));

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
	return frame;
}

TextFrame* DisplayArea::addOption(unsigned int _p, std::string _str,
		GameControl* _gc, void (GameControl::*_f)(unsigned int),
		unsigned int _arg, FONT_SIZE _sz, bool _isSecret, bool _background)
{
	ofLog(OF_LOG_VERBOSE) << "[Display Control] Adding Text " << _str;

	ofPoint pt = ofPoint();
	pt.x = layout[_p].rect.x;
	pt.y = layout[_p].rect.y;

	if (containers.find(_p) == containers.end())
	{

		containers.insert(
				std::pair<unsigned int, TextContainer*>(_p,
						new TextContainer(FLOW_VERTICAL)));

	}

	TextFrame* frame = new TextFrame(40, 40, pt, true, _isSecret);

	frame->setText(_str);
	frame->setFontSize(_sz);
	frame->setMargin(MARGIN_TOP, 64);
	frame->setMargin(MARGIN_RIGHT, 64);
	frame->setMargin(MARGIN_LEFT, 64);
	frame->setMargin(MARGIN_BOTTOM, 0);
	frame->setCallback(_gc, _f, _arg);

	if(_background)
	{
		frame->setBackground();
	}

	containers[_p]->addChild(frame);


	if (fontLarge != nullptr)
		setFont(FONT_LARGE, fontLarge);
	if (fontMedium != nullptr)
		setFont(FONT_MEDIUM, fontMedium);
	if (fontSmall != nullptr)
		setFont(FONT_SMALL, fontSmall);

	readjustHeights();

	return frame;
}

Level* DisplayArea::addBar(unsigned int _p, std::string _str, FONT_SIZE _sz, float _height)
{
	if (containers.find(_p) == containers.end())
	{

		containers.insert(
				std::pair<unsigned int, TextContainer*>(_p,
						new TextContainer(FLOW_HORIZONTAL)));

	}

	Level* level = new Level();
	level->setPosition(ofPoint(layout[_p].rect.x, layout[_p].rect.y));
	level->setWidth(100);
	level->setHeight(_height);
	level->setFontSize(_sz);
	level->setText(_str);
//	TextFrame* frame = new TextFrame(layout[_p].rect.width,
//			layout[_p].rect.height,
//			ofPoint(layout[_p].rect.x, layout[_p].rect.y), false, false);
//	frame->setText(_str);
//	frame->setFontSize(_sz);
//	frame->setMargin(MARGIN_TOP, 8);
//	frame->setMargin(MARGIN_RIGHT, 8);
//	frame->setMargin(MARGIN_LEFT, 8);
//	frame->setMargin(MARGIN_BOTTOM, 8);
//	level->addChild(frame);
	containers[_p]->addChild(level);

	readjustHeights();

	return level;
}

void DisplayArea::clearContent()
{
	for (auto it : containers)
	{
		delete it.second;
	}

	containers.clear();
}

} /* namespace moth */
