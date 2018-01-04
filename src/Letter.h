#pragma once

#include "Symbol.h"

namespace moth
{

class Letter: public Symbol
{
public:

	Letter(ofColor _col);
	virtual ~Letter();

	void display(LAYER _layer);

	float getHeight();
	float getWidth();
	ofPoint getPosition();
	std::string getText(){return text;};
	float getSpacing();
	std::vector<Symbol*> getChildren();

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

protected:

	void calculateSize();
};

} /* namespace moth */

