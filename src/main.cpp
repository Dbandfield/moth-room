#include "ofMain.h"
#include "ofApp.h"

int main( )
{
	ofGLFWWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.width = 1366;
	settings.height = 768;
    ofSetupOpenGL(1366,768, OF_GAME_MODE);
	ofRunApp(new ofApp());
	ofSetLogLevel(OF_LOG_VERBOSE);
}
