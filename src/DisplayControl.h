#pragma once

#include <map>
#include <vector>
#include <string>

#include <ofMain.h>

#include "TextContainer.h"
#include "TextFrame.h"
#include "GameControl.h"
#include "DisplayArea.h"
#include "Level.h"
#include "LevelsFrame.h"

#include "enums.h"

namespace moth
{

class GameControl;
class TextFrame;
class TextContainer;
class DisplayArea;

class DisplayControl
{
public:
	DisplayControl();
	virtual ~DisplayControl();

	void display(LAYER _layer);

	void setFont(FONT_SIZE _sz, ofTrueTypeFont *_f);
	void setLayout(DISPLAY_AREA, std::vector<float> _layout);

	void addText(DISPLAY_AREA _area, unsigned int _p, std::string,
			FONT_SIZE _sz = FONT_SMALL);
	void clearContent(DISPLAY_AREA _area);
	void clearLayout(DISPLAY_AREA _area);
	void addOption(DISPLAY_AREA _area, unsigned int _p, std::string,
			void (GameControl::*_f)(unsigned int), unsigned int _arg,
			FONT_SIZE _sz = FONT_SMALL, bool _isSecret = false,
			bool _background = false, FLOW _flow=FLOW_VERTICAL);

	void onKeyPressed(ofKeyEventArgs &_args);
	void onArrow(int _key);
	void onSelect();

	void setGameControl(GameControl *_gameControl);

	void setLevel(LEVEL _level, float _value);

	void setCorruption(int _corruption);

protected:

	std::vector<Symbol*> getSymbols();

	GameControl* gameControl;

	std::map<LEVEL, Level*> levelMap;

	std::map<DISPLAY_AREA, DisplayArea*> areas;
	std::vector<TextFrame*> options;

	ofColor backgroundColour;
	ofColor textColour;

	int selected;

	ofTrueTypeFont* fontLarge;
	ofTrueTypeFont* fontMedium;
	ofTrueTypeFont* fontSmall;
};

} /* namespace moth */

