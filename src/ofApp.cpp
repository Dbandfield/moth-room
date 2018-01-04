#include "ofApp.h"

ofApp::~ofApp()
{
	delete gameControl;
	delete displayControl;
}

//--------------------------------------------------------------
void ofApp::setup()
{
	ofLog(OF_LOG_VERBOSE) << "[ofApp] Setup";

	pixelate.load("shaders/pixelate");
	vignette.load("shaders/vignette");
	corrupt.load("shaders/corrupt");

	fontsTransferred = false;
	locationsTransferred = false;

	dataLoader = new moth::DataLoader();

	ofSetWindowTitle("Oh no! You are a Moth!");
	ofSetFrameRate(60);
	ofSetLogLevel(OF_LOG_VERBOSE);

	dataLoader->load();

	ofLog(OF_LOG_VERBOSE) << "[ofApp] Creating Controls";

	displayControl = new moth::DisplayControl();
	gameControl = new moth::GameControl();
	displayControl->setGameControl(gameControl);
	gameControl->setDisplayControl(displayControl);

	bufPixelate.allocate(1366, 768);
	bufVignette.allocate(1366, 768);
	bufCorrupt.allocate(1366, 768);

	distort = 0.f;
	dividor = 0;
	dividorChange = 0.1;

	backgroundColour = ofColor();
	backgroundColour.setHsb(0, 0, 30);

}

//--------------------------------------------------------------
void ofApp::update()
{
	dataLoader->update();

	if (!fontsTransferred)
	{
		if (dataLoader->areFontsLoaded())
		{
			ofLog(OF_LOG_VERBOSE)
					<< "[ofApp] Font is loaded, transferring to display control";

			displayControl->setFont(moth::FONT_LARGE,
					&(dataLoader->getFont(moth::FONT_LARGE)));
			displayControl->setFont(moth::FONT_MEDIUM,
					&(dataLoader->getFont(moth::FONT_MEDIUM)));
			displayControl->setFont(moth::FONT_SMALL,
					&(dataLoader->getFont(moth::FONT_SMALL)));
			fontsTransferred = true;
		}
	}

	if (!locationsTransferred)
	{
		if (dataLoader->areLocationsLoaded())
		{
			ofLog(OF_LOG_VERBOSE)
					<< "[ofApp] Locations loaded, transferring to game control";
			gameControl->setLocations(dataLoader->getLocations());
			gameControl->locationsReady();
		}

		locationsTransferred = true;
	}

	distort = sin(ofGetElapsedTimeMillis() / dividor) * 7;
	distort -= 2;
	distort = std::max(0.f, distort);
	distort = std::min(distort, 5.f);
	dividor += dividorChange;

	if (dividor > 5)
	{
		dividorChange = -0.01;
	}
	else if (dividor < 0)
	{
		dividorChange = 0.01;
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{

	// PIXELATE

	bufPixelate.begin();
	ofBackground(backgroundColour);

	if (displayControl != nullptr)
		displayControl->display(moth::LAYER_JITTER);
	if (displayControl != nullptr)
		displayControl->display(moth::LAYER_PIXELLATED);


	bufPixelate.end();

	// CORRUPT
	bufCorrupt.begin();
    ofClear(255,255,255, 0);
	if (displayControl != nullptr)
		displayControl->display(moth::LAYER_DISTORTED);
	bufCorrupt.end();

	// VIGNETTE
	bufVignette.begin();

	pixelate.begin();
	pixelate.setUniform1f("distort", distort);
	bufPixelate.draw(0, 0);
	pixelate.end();

	corrupt.begin();
	bufCorrupt.draw(0, 0);
	corrupt.end();

	bufVignette.end();

	vignette.begin();
	bufVignette.draw(0, 0);

	vignette.end();
}

