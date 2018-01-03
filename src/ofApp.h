#pragma once

#include <algorithm>

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

	ofShader pixelate;
	ofShader vignette;
	ofFbo buf1;
	ofFbo buf2;

	float distort;
	float dividor;
	float dividorChange = 0.1;

	ofTrueTypeFont *font;

	bool fontsTransferred;
	bool locationsTransferred;

	ofColor backgroundColour;

};
