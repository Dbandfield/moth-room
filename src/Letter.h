#pragma once

#include "Symbol.h"

namespace moth
{

class Letter: public Symbol
{
public:

	Letter(ofColor _col);
	virtual ~Letter();

	void setFont(FONT_SIZE _sz, ofTrueTypeFont *_font);
	void setFontSize(FONT_SIZE _sz);

	void setCharacter(char _c);
	void setCharacter(char* _c);
	void setCharacter(std::string _c);

	void display();

	float getHeight();
	float getWidth();
	ofPoint getPosition();
	std::string getText(){return text;};
	float getSpacing();

	void setColour(ofColor _col);

	void setPosition(ofPoint _pt);

protected:

	void calculateSize();
	FONT_SIZE fontSize;
	ofTrueTypeFont *currentFont;
	ofTrueTypeFont *smallFont;
	ofTrueTypeFont *mediumFont;
	ofTrueTypeFont *largeFont;
	std::string text;
	ofColor colour;
};

} /* namespace moth */

