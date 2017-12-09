#pragma once
#include <map>
#include <string>
#include <sstream>

#include <ofMain.h>
#include <ofxXmlSettings.h>

#include "enums.h"
#include "Location.h"
#include "StoryNode.h"

namespace moth
{
typedef std::pair<FONT_SIZE, ofTrueTypeFont> fontPair;
typedef std::map<FONT_SIZE, ofTrueTypeFont> mFont;
typedef std::map<FONT_SIZE, ofTrueTypeFont>::iterator iFont;
class DataLoader
{
public:
	DataLoader();
	virtual ~DataLoader();
	void load();

	ofTrueTypeFont& getFont(FONT_SIZE _size);
	std::vector<Location*> getLocations();

	void update();
	bool areFontsLoaded();
	bool areLocationsLoaded();

protected:
	void loadConfig();
	void loadFonts();
	void loadLocations();
	ofBuffer getBufferFromFile(std::string _fileName);

	void stripHeader(std::string &str, char del1='[', char del2=']');

	/* FONTS */
	mFont fonts;
	bool fontHeaderFound;
	bool allFontsLoaded;

	std::string fontPath;

	const int SZ_SMALL = 16;
	const int SZ_MEDIUM = 24;
	const int SZ_LARGE = 48;

	/* LOCATIONS */
	bool allLocationsLoaded;
	std::vector<Location*> locations;
	const std::string LOCATION_DIR;
	const std::string LOCATION_NAME;
	ofxXmlSettings locationsXml;

	ofFile locationFile;
	std::string pathToLocationFile;
	ofBuffer locationBuf;

	/* CONFIG */

	ofFile   configFile;
	std::string   pathToConfig;
	ofBuffer configBuf;

	const std::string CONFIG_DIR;
	const std::string CONFIG_NAME;

};

} /* namespace moth */
