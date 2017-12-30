#pragma once

#include "Symbol.h"

namespace moth
{

class Letter: public Symbol
{
public:

	Letter(ofColor _col);
	virtual ~Letter();

	void display();

	float getHeight();
	float getWidth();
	ofPoint getPosition();
	std::string getText(){return text;};
	float getSpacing();
	std::vector<Symbol*> getChildren();

	void setText(char _c);
	void setText(char* _c);
	void setText(std::string _c);

	void setFont(FONT_SIZE _sz, ofTrueTypeFont *_font);
	void setFontSize(FONT_SIZE _sz);

	void setPosition(ofPoint _pt);

	void setColour(ofColor _col);

protected:

	void calculateSize();
	FONT_SIZE fontSize;
	ofTrueTypeFont *currentFont;
	ofTrueTypeFont *smallFont;
	ofTrueTypeFont *mediumFont;
	ofTrueTypeFont *largeFont;
};

} /* namespace moth */

