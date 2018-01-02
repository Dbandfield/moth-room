#pragma once

#include "Symbol.h"
#include "TextFrame.h"

namespace moth
{

struct Cell
{
	Cell()
	{
	}
	;
	Cell(unsigned int _row, unsigned int _col, float _percent, int x, int y,
			int w, int h)
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

class DisplayArea: public Symbol
{
public:
	DisplayArea();
	virtual ~DisplayArea();

	/* Inherited */

	void display();

	std::vector<Symbol*> getChildren();

	float getHeight();
	float getWidth();
	ofPoint getPosition();
	std::string getText();
	float getSpacing();

	void setText(char _c);
	void setText(char* _c);
	void setText(std::string _c);

	void addChild(Symbol* _symbol);

	void setFont(FONT_SIZE _sz, ofTrueTypeFont *_font);
	void setFontSize(FONT_SIZE _sz);

	void setPosition(ofPoint _pt);

	void setColour(ofColor _col);

	void setWidth(float _width);

	/* not inherited */

	void clearLayout();
	void clearContent();
	void setLayout(std::vector<float> _layout);

	bool setIndex(unsigned int _index);

	TextFrame* addText(unsigned int _p, std::string,
			FONT_SIZE _sz = FONT_SMALL);
	TextFrame* addOption(unsigned int _p, std::string, GameControl* _gc,
			void (GameControl::*_f)(unsigned int), unsigned int _arg,
			FONT_SIZE _sz = FONT_SMALL, bool _isSecret = false);

protected:
	void readjustHeights();

	std::vector<float> percentages;

	std::map<unsigned int, Cell> layout;
	unsigned int numCells;

	unsigned int index;

	std::map<unsigned int, Symbol*> containers;
};

} /* namespace moth */
