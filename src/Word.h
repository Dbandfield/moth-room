#pragma once

#include "Symbol.h"
#include "Letter.h"

namespace moth
{

class Letter;

class Word: public Symbol
{
public:
	Word(ofColor _col);
	virtual ~Word();

	void display();

	float getHeight();
	float getWidth();
	ofPoint getPosition();
	std::string getText();
	float getSpacing();
	std::vector<Symbol*> getChildren();

	void setText(char _c);
	void setText(char* _c);
	void setText(std::string _c);

	void addChild(Symbol* _symbol);

	void setFont(FONT_SIZE _sz, ofTrueTypeFont *_font);
	void setFontSize(FONT_SIZE _sz);

	void setColour(ofColor _col);

	void setPosition(ofPoint _pt);

protected:

	void calculateSize();
};

} /* namespace moth */
