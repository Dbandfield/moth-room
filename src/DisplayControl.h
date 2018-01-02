#pragma once

#include <map>
#include <vector>
#include <string>

#include <ofMain.h>

#include "TextContainer.h"
#include "TextFrame.h"
#include "GameControl.h"
#include "DisplayArea.h"

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

	void display();

	void setFont(FONT_SIZE _sz, ofTrueTypeFont *_f);
	void setLayout(DISPLAY_AREA, std::vector<float> _layout);

	void addText(DISPLAY_AREA _area, unsigned int _p, std::string, FONT_SIZE _sz=FONT_SMALL);
	void clearContent();
	void clearLayout();
	void addOption(DISPLAY_AREA _area, unsigned int _p, std::string, void(GameControl::*_f)(unsigned int), unsigned int _arg, FONT_SIZE _sz=FONT_SMALL, bool _isSecret=false);

	void onKeyPressed(ofKeyEventArgs &_args);
	void onArrow(int _key);
	void onSelect();

	void setGameControl(GameControl *_gameControl);

protected:

	std::vector<Symbol*> getSymbols();

	GameControl* gameControl;

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

