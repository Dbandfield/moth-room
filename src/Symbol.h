#pragma once

#include <string>

#include "ofMain.h"

#include "enums.h"

namespace moth
{

class Symbol
{
public:
	Symbol()
	{
	}
	;
	virtual ~Symbol()
	{
	}
	;

	virtual void display(LAYER _layer) = 0;

	virtual std::vector<Symbol*> getChildren() = 0;

	virtual float getHeight() = 0;
	virtual float getWidth() = 0;
	virtual ofPoint getPosition() = 0;
	virtual std::string getText() = 0;
	virtual float getSpacing() = 0;

	virtual void setText(char _c) = 0;
	virtual void setText(char* _c) = 0;
	virtual void setText(std::string _c) = 0;

	virtual void addChild(Symbol* _symbol) = 0;

	virtual void setFont(FONT_SIZE _sz, ofTrueTypeFont *_font) = 0;
	virtual void setFontSize(FONT_SIZE _sz) = 0;

	virtual void setPosition(ofPoint _pt) = 0;

	virtual void setColour(ofColor _col) = 0;

	virtual void setWidth(float _width) = 0;

	virtual void setLayer(LAYER _layer) = 0;

	virtual void setBackground() = 0;


protected:

	ofColor colCurrent;

	std::vector<Symbol*> children;

	std::string text;
	ofPoint position;
	float width;
	float height;

	FONT_SIZE fontSize;

	ofTrueTypeFont* currentFont;
	ofTrueTypeFont* fontLarge;
	ofTrueTypeFont* fontMedium;
	ofTrueTypeFont* fontSmall;

	LAYER layer;
};

} /* namespace moth */

