#pragma once

#include <string>

#include "ofMain.h"

#include "enums.h"

namespace moth
{

class Symbol
{
public:
	Symbol(){};
	virtual ~Symbol(){};


	virtual void display() = 0;


	virtual float getHeight() = 0;
	virtual float getWidth() = 0;
	virtual ofPoint getPosition() = 0;
	virtual std::string getText() = 0;
	virtual float getSpacing() = 0;


	virtual void setCharacter(char _c) = 0;
	virtual void setCharacter(char* _c) = 0;
	virtual void setCharacter(std::string _c) = 0;

	virtual void setFont(FONT_SIZE _sz, ofTrueTypeFont *_font) = 0;
	virtual void setFontSize(FONT_SIZE _sz) = 0;

	virtual void setPosition(ofPoint _pt) = 0;

	virtual void setColour(ofColor _col) = 0;

protected:
	virtual void calculateSize()= 0;


	ofPoint position;
	float width;
	float height;
};

} /* namespace moth */
