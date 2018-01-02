#pragma once

#include <map>
#include <vector>
#include <string>

#include <ofMain.h>

#include "TextContainer.h"
#include "TextFrame.h"
#include "GameControl.h"

#include "enums.h"

namespace moth
{

class GameControl;
class TextFrame;
class TextContainer;

struct Cell
{
	Cell(){};
	Cell(unsigned int _row, unsigned int _col, float _percent, int x, int y, int w, int h)
	{
		row = _row;
		col = _col;
		percent = _percent;
		rect = ofRectangle(x, y, w, h);
	}

	ofRectangle rect;
	unsigned int col;
	unsigned int row;
	float percent;
};

class DisplayControl
{
public:
	DisplayControl();
	virtual ~DisplayControl();

	void display();

	void clearLayout();
	void setLayout(std::vector<float> _layout);

	void setFont(FONT_SIZE _sz, ofTrueTypeFont *_f);

	void addText(unsigned int _p, std::string, FONT_SIZE _sz=FONT_SMALL);
	void clearContent();
	void addOption(unsigned int _p, std::string, void(GameControl::*_f)(unsigned int), unsigned int _arg, FONT_SIZE _sz=FONT_SMALL, bool _isSecret=false);

	void onKeyPressed(ofKeyEventArgs &_args);
	void onArrow(int _key);
	void onSelect();

	void setGameControl(GameControl *_gameControl);

protected:
	void readjustHeights();

	std::vector<Symbol*> getSymbols();

	GameControl* gameControl;

	std::map<unsigned int, Cell> layout;
	unsigned int numCells;

	std::map<unsigned int, TextContainer*> containers;
	std::vector<TextFrame*> options;

	ofColor backgroundColour;
	ofColor textColour;

	int selected;

	ofTrueTypeFont* fontLarge;
	ofTrueTypeFont* fontMedium;
	ofTrueTypeFont* fontSmall;

//	Animator *animator;
};

} /* namespace moth */

