#pragma once

#include "ofMain.h"

#include "DisplayControl.h"
#include "GameControl.h"
#include "DataLoader.h"
#include "enums.h"

class ofApp: public ofBaseApp
{

public:
	~ofApp();

	void setup();
	void update();
	void draw();

protected:

	moth::GameControl *gameControl;
	moth::DisplayControl *displayControl;
	moth::DataLoader *dataLoader;

	ofTrueTypeFont *font;

	bool fontsTransferred;

};
