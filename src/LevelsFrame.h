#pragma once

#include "Symbol.h"

namespace moth
{

class LevelsFrame: public Symbol
{
public:
	LevelsFrame();
	~LevelsFrame();

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

	void setFont(FONT_SIZE _sz, ofTrueTypeFont *_font);
	void setFontSize(FONT_SIZE _sz);

	void setPosition(ofPoint _pt);

	void setColour(ofColor _col);

protected:

	void calculateSize();
};

} /* namespace moth */

