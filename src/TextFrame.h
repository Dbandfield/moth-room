#pragma once

#include <vector>
#include <string>
#include <algorithm>

#include "ofMain.h"

#include "GameControl.h"
#include "Symbol.h"
#include "Option.h"
#include "Letter.h"

#include "enums.h"

namespace moth
{
class GameControl;
class Option;

class TextFrame
{
public:
	TextFrame(float _width, float _height, ofPoint _position, bool _isOption=false, bool _isSecret=false);
	virtual ~TextFrame();

	void display();

	void setText(std::string _str);

	void setFont(FONT_SIZE _sz, ofTrueTypeFont *_font);
	void setFontSize(FONT_SIZE _sz);

	void setCallback(GameControl *_gameControl, void(GameControl::*_f)(unsigned int), unsigned int _arg);

	void setIsSecret(bool _isSecret);

	float getHeight();

	void setPosition(float _x, float _y);
	void setWidth(float _w);
	void setHeight(float _h);
	void setSelected(bool _sel);
	void setMargin(MARGIN, float _amt);

	void onSelect();

protected:
	void recalculatePositions();
	Option* opt;

	float selectedMod;
	ofColor colStatic;
	ofColor colCurrent;
	ofColor colIsSecret;
	ofColor colBase;

	bool isOption;
	bool isSecret;

	std::vector<Symbol*> symbols;

	ofTrueTypeFont* fontLarge;
	ofTrueTypeFont* fontMedium;
	ofTrueTypeFont* fontSmall;


	ofPoint position;
	ofPoint adjustedPosition;
	float width;
	float height;
	float marginLeft;
	float marginTop;
	float marginRight;
	float marginBottom;

	float letterSpacing;
	/* Multiply letter height by this to get line height.
	 * letter height is a bit too small for lines
	 */
	const float LINE_HEIGHT_ADJUST = 1.4;



};

} /* namespace moth */

