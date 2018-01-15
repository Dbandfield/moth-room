#pragma once

#include <algorithm>

#include "Symbol.h"
#include "TextFrame.h"
#include "BackgroundDecorator.h"
#include "Level.h"
#include "Word.h"

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
	DisplayArea(ofPoint _pos, float _width, float _height);
	virtual ~DisplayArea();

	/* Inherited */

	void display(LAYER _layer);

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

	void setLayer(LAYER _layer);

	void setBackground(){};



	/* not inherited */

	void clearLayout();
	void clearContent();
	void setLayout(std::vector<float> _layout);

	bool setIndex(unsigned int _index);

	TextFrame* addText(unsigned int _p, std::string,
			FONT_SIZE _sz = FONT_SMALL);

	TextFrame* addOption(unsigned int _p, std::string, GameControl* _gc,
			void (GameControl::*_f)(Args), Args _arg,
			FONT_SIZE _sz = FONT_SMALL, bool _isSecret = false,
			bool _background = false, FLOW _flow = FLOW_VERTICAL);

	Level* addBar(unsigned int _p, std::string _str, FONT_SIZE _sz,
			float _height);

	void setCorruption(int _corruption);

protected:
	void readjustHeights();

	void addWords(std::vector<Symbol*> _words);

	std::vector<float> percentages;

	std::map<unsigned int, Cell> layout;
	unsigned int numCells;

	unsigned int index;

	std::map<unsigned int, Symbol*> containers;

	std::vector<Symbol*> words;

	int corruption;
};

} /* namespace moth */
