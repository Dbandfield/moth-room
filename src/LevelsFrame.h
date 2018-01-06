#pragma once

#include "Symbol.h"

namespace moth
{

class LevelsFrame: public Symbol
{
public:
	LevelsFrame();
	~LevelsFrame();

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

	/* not inherited */

	void setHeight(float _height);

	void setBackground(){};

protected:

};

} /* namespace moth */

