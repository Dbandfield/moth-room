#pragma once
#include <map>
#include <string>

#include <ofMain.h>

#include "enums.h"

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

	void update();
	bool isLoaded();

protected:
	void stripHeader(std::string &str);
	mFont fonts;

	ofFile   configFile;
	std::string   pathToConfig;
	ofBuffer fileBuf;

	const std::string CONFIG_DIR;
	const std::string CONFIG_NAME;

	bool fontHeaderFound;
	bool allLoaded;

	std::string fontPath;

	const int SZ_SMALL = 12;
	const int SZ_MEDIUM = 24;
	const int SZ_LARGE = 48;
};

} /* namespace moth */
