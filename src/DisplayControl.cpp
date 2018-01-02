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

	DisplayArea* levels = new DisplayArea();
	DisplayArea* main = new DisplayArea();
	DisplayArea* buttons = new DisplayArea();
	areas.insert(std::pair<DISPLAY_AREA, DisplayArea*>(AREA_LEVELS, levels));
	areas.insert(std::pair<DISPLAY_AREA, DisplayArea*>(AREA_MAIN, main));
	areas.insert(std::pair<DISPLAY_AREA, DisplayArea*>(AREA_BUTTONS, buttons));

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
	for (auto i : areas)
	{
		std::vector<Symbol*> frameSym = i.second->getChildren();
		sym.insert(sym.end(), frameSym.begin(), frameSym.end());
	}

	return sym;
}

void DisplayControl::setLayout(DISPLAY_AREA _area, std::vector<float> _layout)
{
	areas[_area]->setLayout(_layout);
}


void DisplayControl::display()
{
	ofBackground(backgroundColour);
	ofSetColor(textColour);

	for (auto it : areas)
	{
		it.second->display();
	}

}

void DisplayControl::setFont(FONT_SIZE _sz, ofTrueTypeFont *_f)
{
	ofLog(OF_LOG_VERBOSE) << "[Display Control] Setting Font";

	for (auto it : areas)
	{
		ofLog(OF_LOG_VERBOSE) << "[Display Control] Setting Font txt ";

		it.second->setFont(_sz, _f);
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
}



void DisplayControl::clearContent()
{
	ofLog(OF_LOG_VERBOSE) << "[Display Control] Clearing options";
	for (auto it : areas)
	{
		it.second->clearContent();
	}
	options.clear();
}

void DisplayControl::clearLayout()
{
	ofLog(OF_LOG_VERBOSE) << "[Display Control] Clearing layout";
	for (auto it : areas)
	{
		it.second->clearLayout();
	}
}
void DisplayControl::addText(DISPLAY_AREA _area, unsigned int _p, std::string _str, FONT_SIZE _sz)
{
	areas[_area]->addText(_p, _str, _sz);
}

void DisplayControl::addOption(DISPLAY_AREA _area, unsigned int _p, std::string _str,
		void (GameControl::*_f)(unsigned int), unsigned int _arg, FONT_SIZE _sz,
		bool _isSecret)
{
	TextFrame* fr = areas[_area]->addOption(_p, _str, gameControl, _f, _arg, _sz, _isSecret);

	options.push_back(fr);

	for(size_t i = 0; i < options.size(); i ++)
	{
		options[i]->setSelected(i == selected);
	}
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
