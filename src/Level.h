#pragma once

#include "Symbol.h"

namespace moth
{

class Level: public Symbol
{
public:
	Level();
	virtual ~Level();

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

	/* --- Not inherited --- */

	void setWidth(float _width);
	void setHeight(float _height);

protected:

	void calculateSize();
};

} /* namespace moth */
