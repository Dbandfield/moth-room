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

	ofShader jitter;
	ofShader pixelate;
	ofShader vignette;
	ofShader corrupt;
	ofFbo bufJitter;
	ofFbo bufPixelate;
	ofFbo bufVignette;
	ofFbo bufCorrupt;

	float distort;
	float dividor;
	float dividorChange = 0.1;

	ofTrueTypeFont *font;

	bool fontsTransferred;
	bool locationsTransferred;
	bool secretsTransferred;
	bool skillsTransferred;

	ofColor backgroundColour;

};
