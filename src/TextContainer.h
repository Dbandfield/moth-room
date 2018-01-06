#pragma once

#include <vector>
#include <string>

#include <ofMain.h>

#include "GameControl.h"
#include "TextFrame.h"
#include "enums.h"
#include "Symbol.h"
#include "BorderDecorator.h"

namespace moth
{

class GameControl;
class TextFrame;
class Symbol;

class TextContainer : public Symbol
{
public:
	TextContainer(FLOW _flow);
	virtual ~TextContainer();

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

	void setLayer(LAYER _layer);



	/* Not inherited */

	void setPosition(float _x, float _y);
	void setWidth(float _w);

	unsigned int getSize(){return children.size();};

	std::vector<Symbol*> getSymbols();

	void setBackground();
	void setMargin(MARGIN, float _amt);


protected:

	FLOW flow;

	float marginLeft;
	float marginRight;
	float marginTop;
	float marginBottom;

};

} /* namespace moth */

