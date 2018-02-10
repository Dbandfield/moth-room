#pragma once

#include <vector>
#include <string>

#include <ofMain.h>

#include "enums.h"
#include "Symbol.h"

namespace moth
{

class GameControl;
class Symbol;
class TextFrame;

class TextContainer : public Symbol
{
public:
	TextContainer(FLOW _flow);
	virtual ~TextContainer();

	/* Inherited */

	virtual void display(LAYER _layer);

	std::vector<Symbol*> getChildren();

	virtual float getHeight();
	virtual float getWidth();
	ofPoint getPosition();
	std::string getText();
	float getSpacing();

	void setText(char _c);
	void setText(char* _c);
	void setText(std::string _c);

	virtual void addChild(Symbol* _symbol);

	void setFont(FONT_SIZE _sz, ofTrueTypeFont *_font);
	void setFontSize(FONT_SIZE _sz);

	virtual void setPosition(ofPoint _pt);

	void setColour(ofColor _col);

	void setLayer(LAYER _layer);



	/* Not inherited */

	virtual void setPosition(float _x, float _y);
	virtual void setWidth(float _w);

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

