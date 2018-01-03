#pragma once

#include "Symbol.h"
#include "Letter.h"

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

	void addChild(Symbol* _symbol);

	void setFont(FONT_SIZE _sz, ofTrueTypeFont *_font);
	void setFontSize(FONT_SIZE _sz);

	void setPosition(ofPoint _pt);

	void setColour(ofColor _col);
	void setWidth(float _width);


	/* --- Not inherited --- */

	void setHeight(float _height);

protected:
	void readjustDimensions();

	float barWidth;
	float barMaxHeight;
	float barPercent;

	float marginTop;
	float marginBottom;
	float marginLeft;
	float marginRight;

	ofPoint barPos;
	std::vector<ofPoint> textPos;

};

} /* namespace moth */
