#pragma once

#include <vector>
#include <string>

#include <ofMain.h>

#include "GameControl.h"
#include "TextFrame.h"
#include "enums.h"
namespace moth
{

class GameControl;
class TextFrame;

class TextContainer
{
public:
	TextContainer();
	virtual ~TextContainer();

	void addTextFrame(float _width, float _height, ofPoint _position, bool _isOption=false);

	void display();

	void setText(unsigned int _ID, std::string _str);

	void setFont(unsigned int _ID, FONT_SIZE _sz, ofTrueTypeFont *_font);
	void setFontSize(unsigned int _ID, FONT_SIZE _sz);

	void setCallback(unsigned int _ID, GameControl *_gameControl, void(GameControl::*_f)(unsigned int), unsigned int _arg);

	float getHeight();

	void setPosition(float _x, float _y);
	void setWidth(float _w);
	void setHeight(float _h);
	void setMargin(unsigned int _id, MARGIN _mgn, float _amt);

	void setIsSecret(unsigned int _id, bool _isSecret);

	unsigned int getSize(){return frames.size();};

	SELECTED_BOUNDS decrementSelected();
	SELECTED_BOUNDS incrementSelected();

	void setSelected(bool _sel, SELECTED_BOUNDS);
	void onSelect();


protected:
	std::vector<TextFrame*> frames;
	int selected;

};

} /* namespace moth */

