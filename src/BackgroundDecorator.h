#pragma once

#include "SymbolDecorator.h"

namespace moth
{
class BackgroundDecorator : public SymbolDecorator
{
public:
	BackgroundDecorator(Symbol* _decorated);
	~BackgroundDecorator();

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

protected:

	void getData();
};
}
