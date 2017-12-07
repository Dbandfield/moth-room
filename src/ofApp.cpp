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
	fontsTransferred = false;
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
}

//--------------------------------------------------------------
void ofApp::update()
{
	dataLoader->update();
	if(!fontsTransferred)
	{
		if(dataLoader->isLoaded())
		{
			ofLog(OF_LOG_VERBOSE) << "[ofApp] Font is loaded, transferring to display control";

			displayControl->setFont(moth::FONT_LARGE, &(dataLoader->getFont(moth::FONT_LARGE)));
			displayControl->setFont(moth::FONT_MEDIUM, &(dataLoader->getFont(moth::FONT_MEDIUM)));
			displayControl->setFont(moth::FONT_SMALL, &(dataLoader->getFont(moth::FONT_SMALL)));
			fontsTransferred = true;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if(displayControl != nullptr) displayControl->display();
}


