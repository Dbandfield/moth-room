#pragma once

#include <vector>
#include <string>
#include <algorithm>

#include "ofMain.h"

#include "GameControl.h"
#include "Symbol.h"
#include "Option.h"
#include "Word.h"
#include "BackgroundDecorator.h"
#include "BorderDecorator.h"

#include "enums.h"

namespace moth
{
class GameControl;
class Option;
class Symbol;

class TextFrame : public Symbol
{
public:
	TextFrame(float _width, float _height, ofPoint _position, bool _isOption=false, bool _isSecret=false);
	virtual ~TextFrame();

	/* --- Inherited --- */

	void display(LAYER _layer);

	float getHeight();
	float getWidth();
	ofPoint getPosition();
	std::string getText();
	float getSpacing();
	std::vector<Symbol*> getChildren(){return children;};

	void setText(char _c);
	void setText(char* _c);
	void setText(std::string _str);

	void addChild(Symbol* _symbol);

	void setFont(FONT_SIZE _sz, ofTrueTypeFont *_font);
	void setFontSize(FONT_SIZE _sz);

	void setPosition(ofPoint _pt);

	void setColour(ofColor _col);

	void setWidth(float _w);

	void setLayer(LAYER _layer);

	void setBackground();


	/* --- End inherited --- */

	void setCallback(GameControl *_gameControl, void(GameControl::*_f)(unsigned int), unsigned int _arg);
	void onSelect();

	void setIsSecret(bool _isSecret);

	void setSelected(bool _sel);
	void setMargin(MARGIN, float _amt);



protected:
	void calculateSize();
	std::vector<std::string> split(const std::string &s, char delimiter);
	void recalculatePositions();
	Option* opt;

	std::string selectMarker;

	float selectedMod; // to modify colour, when selected
	ofColor colStatic;
	ofColor colIsSecret;
	ofColor colBase;

	bool isOption;
	bool isSecret;

	bool smallWord;

	ofPoint adjustedPosition;

	float marginLeft;
	float marginTop;
	float marginRight;
	float marginBottom;

	float letterSpacing;
	/* Multiply letter height by this to get line height.
	 * letter height is a bit too small for lines
	 */
	const float LINE_HEIGHT_ADJUST = 1.6;



};

} /* namespace moth */

