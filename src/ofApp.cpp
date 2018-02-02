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
	jitter.load("shaders/jitter");

	fontsTransferred = false;
	locationsTransferred = false;

	dataLoader = new moth::DataLoader();

	ofSetWindowTitle("THE MOTH GAME");
	ofSetFrameRate(60);
	ofSetLogLevel(OF_LOG_VERBOSE);

	dataLoader->load();

	ofLog(OF_LOG_VERBOSE) << "[ofApp] Creating Controls";

	audioPlayer = new moth::AudioPlayer;
	audioPlayer->setAudio(dataLoader->getAudio());

	displayControl = new moth::DisplayControl();
	gameControl = new moth::GameControl();
	displayControl->setGameControl(gameControl);
	displayControl->setAudioPlayer(audioPlayer);
	gameControl->setDisplayControl(displayControl);

	bufPixelate.allocate(1366, 768);
	bufVignette.allocate(1366, 768);
	bufCorrupt.allocate(1366, 768);
	bufJitter.allocate(1366, 768);

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

	if (!locationsTransferred || !secretsTransferred || !skillsTransferred)
	{
		if (dataLoader->areLocationsLoaded() && dataLoader->areSecretsLoaded()
				&& dataLoader->areSkillsLoaded())
		{
			ofLog(OF_LOG_VERBOSE)
					<< "[ofApp] Locations loaded, transferring to game control";
			gameControl->setLocations(dataLoader->getAllLocations(),
					dataLoader->getMothLocations(),
					dataLoader->getObstacleLocations(),
					dataLoader->getNormalLocations());

			ofLog(OF_LOG_VERBOSE)
					<< "[ofApp] Secrets loaded, transferring to game control";
			gameControl->setSecrets(dataLoader->getSecrets());

			ofLog(OF_LOG_VERBOSE)
					<< "[ofApp] Skills loaded, transferring to game control";
			gameControl->setSkills(dataLoader->getSkills());
		}

		locationsTransferred = true;
		secretsTransferred = true;
		skillsTransferred = true;

		gameControl->locationsReady();

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
	ofClear(255, 255, 255, 0);

	if (displayControl != nullptr)
		displayControl->display(moth::LAYER_PIXELLATED);

	bufPixelate.end();

	// JITTER

	bufJitter.begin();
	ofClear(255, 255, 255, 0);
	if (displayControl != nullptr)
		displayControl->display(moth::LAYER_JITTER);
	bufJitter.end();

	// CORRUPT
	bufCorrupt.begin();
	ofClear(255, 255, 255, 0);
	if (displayControl != nullptr)
		displayControl->display(moth::LAYER_DISTORTED);
	bufCorrupt.end();

	// VIGNETTE
	bufVignette.begin();
	ofBackground(backgroundColour);

	jitter.begin();
	jitter.setUniform1f("distort", distort);
	bufJitter.draw(0, 0);
	jitter.end();

	pixelate.begin();
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

