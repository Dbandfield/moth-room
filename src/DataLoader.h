#pragma once
#include <map>
#include <string>
#include <sstream>

#include <ofMain.h>
#include <ofxXmlSettings.h>

#include "enums.h"
#include "Location.h"
#include "MothLocation.h"
#include "ObstacleLocation.h"
#include "StoryNode.h"
#include "Secret.h"
#include "Skill.h"

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
	std::map<unsigned int, Location*> getAllLocations();
	std::map<unsigned int, MothLocation*> getMothLocations();
	std::map<unsigned int, ObstacleLocation*> getObstacleLocations();
	std::map<unsigned int, Location*> getNormalLocations();
	std::map<unsigned int, Secret*> getSecrets();
	std::map<unsigned int, Skill*> getSkills();
	std::map<AUDIO, ofSoundPlayer*> getAudio();

	void update();
	bool areFontsLoaded();
	bool areLocationsLoaded();
	bool areSecretsLoaded();
	bool areSkillsLoaded();
	bool isAudioLoaded();

protected:
	void loadConfig();
	void loadFonts();
	void loadLocations();
	void loadSecrets();
	void loadSkills();
	void loadAudio();
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

	/* SKILLS */
	std::map<unsigned int, Skill*> m_skills;
	bool allSkillsLoaded;

	const std::string SKILLS_DIR;
	const std::string SKILLS_NAME;
	ofxXmlSettings skillsXml;

	ofFile skillsFile;
	std::string pathToSkillsFile;
	ofBuffer skillsBuf;

	/* SECRETS */
	std::map<unsigned int, Secret*> m_secrets;
	bool allSecretsLoaded;

	const std::string SECRETS_DIR;
	const std::string SECRETS_NAME;
	ofxXmlSettings secretsXml;

	ofFile secretsFile;
	std::string pathToSecretsFile;
	ofBuffer secretsBuf;

	/* LOCATIONS */
	bool allLocationsLoaded;
	std::map<unsigned int, Location*> m_allLocations;
	std::map<unsigned int, MothLocation*> m_mothLocations;
	std::map<unsigned int, ObstacleLocation*> m_obstacleLocations;
	std::map<unsigned int, Location*> m_normalLocations;

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

	/* AUDIO */
	bool allAudioLoaded;
	std::map<AUDIO, ofSoundPlayer*> m_players;

	const std::string AUDIO_DIR;
	const std::string AUDIO_BUTTON_FILE;
	const std::string AUDIO_GO_FILE;
	const std::string AUDIO_EAT_FILE;
	const std::string AUDIO_SECRET_FILE;


};

} /* namespace moth */
