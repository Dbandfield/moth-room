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

	void setFont(FONT_SIZE _sz, ofTrueTypeFont *_font);
	void setFontSize(FONT_SIZE _sz);

	void setColour(ofColor _col);

	void setPosition(ofPoint _pt);

protected:

	void calculateSize();
	FONT_SIZE fontSize;
	ofTrueTypeFont *currentFont;
	ofTrueTypeFont *smallFont;
	ofTrueTypeFont *mediumFont;
	ofTrueTypeFont *largeFont;
};

} /* namespace moth */
