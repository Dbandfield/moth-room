/*
 * mo_font_loader.cpp
 *
 *  Created on: 20 Oct 2017
 *      Author: daniel
 */

#include "DataLoader.h"

namespace moth
{

DataLoader::DataLoader() :
		CONFIG_DIR("config"), CONFIG_NAME("config.cfg"), LOCATION_DIR("xml"), LOCATION_NAME(
				"locations.xml"), SECRETS_DIR("xml"), SECRETS_NAME(
				"secrets.xml"), SKILLS_DIR("xml"), SKILLS_NAME("skills.xml"), AUDIO_DIR(
				"audio"), AUDIO_BUTTON_FILE("button_1.wav"), AUDIO_GO_FILE(
				"go_1.wav"), AUDIO_EAT_FILE("eat_1.wav"), AUDIO_SECRET_FILE(
				"secret_1.wav")
{
	fontHeaderFound = false;
	fonts.insert(fontPair(FONT_SMALL, ofTrueTypeFont()));
	fonts.insert(fontPair(FONT_MEDIUM, ofTrueTypeFont()));
	fonts.insert(fontPair(FONT_LARGE, ofTrueTypeFont()));

	allFontsLoaded = false;
	allLocationsLoaded = false;
	allSecretsLoaded = false;
	allSkillsLoaded = false;
	allAudioLoaded = false;

	m_players[AUDIO_BUTTON] = new ofSoundPlayer();
	m_players[AUDIO_GO] = new ofSoundPlayer();
	m_players[AUDIO_EAT] = new ofSoundPlayer();
	m_players[AUDIO_SECRET] = new ofSoundPlayer();
}

DataLoader::~DataLoader()
{

}

void DataLoader::stripHeader(std::string &str, char del1, char del2)
{
	int openBracket = -1;
	int closeBracket = -1;

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == del1)
		{
			openBracket = i;
			break;
		}
	}

	if (openBracket == -1)
		return;

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == del2)
		{
			closeBracket = i;
			break;
		}
	}

	if (closeBracket == -1)
		return;

	str = str.substr(openBracket + 1, (closeBracket - openBracket) - 1);
	return;

}

void DataLoader::load()
{
	loadConfig();
	loadFonts();
	loadLocations();
	loadSkills();
	loadSecrets();
	loadAudio();
}

void DataLoader::loadAudio()
{
	m_players[AUDIO_BUTTON]->load(ofFilePath::join(AUDIO_DIR, AUDIO_BUTTON_FILE));
	m_players[AUDIO_GO]->load(ofFilePath::join(AUDIO_DIR, AUDIO_GO_FILE));
	m_players[AUDIO_EAT]->load(ofFilePath::join(AUDIO_DIR, AUDIO_EAT_FILE));
	m_players[AUDIO_SECRET]->load(ofFilePath::join(AUDIO_DIR, AUDIO_SECRET_FILE));

	allAudioLoaded = true;
}

std::map<AUDIO, ofSoundPlayer*> DataLoader::getAudio()
{
	return m_players;
}

void DataLoader::loadConfig()
{
	// First load config
	pathToConfig = ofFilePath::join(CONFIG_DIR, CONFIG_NAME);

	configBuf = getBufferFromFile(pathToConfig);

	for (ofBuffer::Line it = configBuf.getLines().begin();
			it != configBuf.getLines().end(); it++)
	{
		std::string line = *it;
		if (!line.empty())
		{
			if (line[0] != '#') // comments
			{
				if (line[0] == '[') // setting header
				{
					stripHeader(line);
					if (line == "fonts")
					{
						fontHeaderFound = true;
					}
					else
					{
						fontHeaderFound = false;
					}

				}
				else
				{
					if (fontHeaderFound)
					{
						std::string toFind = "font_path";
						size_t ndx1 = line.find(toFind);

						if (ndx1 != std::string::npos)
						{
							std::string equals = "=";
							size_t ndx2 = line.find(equals);
							if (ndx2 != std::string::npos)
							{
								if (ndx2 + equals.size() < line.size() - 1)
								{
									fontPath = line.substr(ndx2 + 1);
								}
							}
						}

					}
				}
			}
		}
	}

}

void DataLoader::loadFonts()
{

	ofFile *fontFileTest = new ofFile();
	fontFileTest->open(fontPath);

	if (!fontFileTest->isFile())
	{
		ofLog(OF_LOG_ERROR) << "Error: Font path not specified in "
				<< pathToConfig;
		throw std::runtime_error("No font path specified");
	}

	delete fontFileTest;

	for (iFont it = fonts.begin(); it != fonts.end(); it++)
	{
		if (it->first == FONT_SMALL)
			it->second.load(fontPath, SZ_SMALL);
		else if (it->first == FONT_MEDIUM)
			it->second.load(fontPath, SZ_MEDIUM);
		else if (it->first == FONT_LARGE)
			it->second.load(fontPath, SZ_LARGE);
	}
}

ofBuffer DataLoader::getBufferFromFile(std::string _filename)
{
	ofFile file;
	ofBuffer buf("");

	if (file.doesFileExist(_filename))
	{
		file.open(_filename, ofFile::Mode::ReadOnly, false);
		buf = file.readToBuffer();
	}
	else
	{
		ofLog(OF_LOG_ERROR) << "[ERROR][DataLoader] Could not find file: "
				<< _filename;
		throw std::runtime_error("File does not exist");
	}

	return buf;
}

std::map<unsigned int, Location*> DataLoader::getAllLocations()
{
	return m_allLocations;
}

std::map<unsigned int, MothLocation*> DataLoader::getMothLocations()
{
	return m_mothLocations;
}

std::map<unsigned int, ObstacleLocation*> DataLoader::getObstacleLocations()
{
	return m_obstacleLocations;
}

std::map<unsigned int, Location*> DataLoader::getNormalLocations()
{
	return m_normalLocations;
}

std::map<unsigned int, Skill*> DataLoader::getSkills()
{
	return m_skills;
}

bool DataLoader::areSkillsLoaded()
{
	return allSkillsLoaded;
}

bool DataLoader::areSecretsLoaded()
{
	return allSecretsLoaded;
}

void DataLoader::loadSkills()
{
	ofLog() << "[DATA_LOADER] - loading secrets";

	pathToSkillsFile = ofFilePath::join(SKILLS_DIR, SKILLS_NAME);
	skillsXml.loadFile(pathToSkillsFile);

	int numSkills = skillsXml.getNumTags("skill");

	for (int i = 0; i < numSkills; i++)
	{
		skillsXml.pushTag("skill", i);
		std::stringstream idSS;
		unsigned int id;
		idSS << skillsXml.getValue("id", "[ERROR] - no id in skill from xml");
		idSS >> id;

		std::string txt = skillsXml.getValue("text",
				"[ERROR] - no skill text in xml");

		ofLog() << "[DATA_LOADER] - loading skill " << txt;

		m_skills.insert(
				std::pair<unsigned int, Skill*>(id, new Skill(txt, id)));

		skillsXml.popTag();

	}

	allSkillsLoaded = true;
}

void DataLoader::loadSecrets()
{
	ofLog() << "[DATA_LOADER] - loading secrets";
	pathToSecretsFile = ofFilePath::join(SECRETS_DIR, SECRETS_NAME);
	secretsXml.loadFile(pathToSecretsFile);

	int numSecrets = secretsXml.getNumTags("secret");

	for (int i = 0; i < numSecrets; i++)
	{
		secretsXml.pushTag("secret", i);
		std::stringstream idSS;
		unsigned int id;
		idSS << secretsXml.getValue("id", "[ERROR] - no id in secret from xml");
		idSS >> id;

		std::string shortTxt = secretsXml.getValue("short",
				"[ERROR] - no secret short in xml");

		std::string txt = secretsXml.getValue("text",
				"[ERROR] - no secret text in xml");

		ofLog() << "[DATA_LOADER] - loading secret " << shortTxt;

		m_secrets.insert(
				std::pair<unsigned int, Secret*>(id,
						new Secret(shortTxt, txt, id)));

		secretsXml.popTag();

	}

	allSecretsLoaded = true;
}

std::map<unsigned int, Secret*> DataLoader::getSecrets()
{
	return m_secrets;
}

void DataLoader::loadLocations()
{
	ofLog(OF_LOG_VERBOSE) << "[DataLoader] Loading Locations";
	pathToLocationFile = ofFilePath::join(LOCATION_DIR, LOCATION_NAME);
	locationsXml.loadFile(pathToLocationFile);

	int numLocations = locationsXml.getNumTags("location");
	if (numLocations > 0)
	{
		for (int i = 0; i < numLocations; i++)
		{
			ofLog(OF_LOG_VERBOSE) << "[DataLoader] Loading Location number: "
					<< i;

			// GO INTO LOCATION TAGS
			locationsXml.pushTag("location", i);
			int numNodes = locationsXml.getNumTags("node");
			unsigned int numLinks = locationsXml.getNumTags("link");

			// GET LOCATION ID
			std::stringstream locIdSs;
			locIdSs << locationsXml.getValue("id", "");
			unsigned int locId;
			locIdSs >> locId;

			// GET LOCATION DESCRIPTION
			std::string locDesc = locationsXml.getValue("description",
					"INVALID");

			// GET LOCATION TYPE
			std::string type = locationsXml.getValue("type", "ERROR_NO_TYPE");

			float x = std::stof(locationsXml.getValue("x", ""));
			float y = std::stof(locationsXml.getValue("y", ""));

			Location* loc;

			// NORMAL
			if (type == "normal")
			{
				loc = new Location(locDesc, locId, x, y);
				m_normalLocations.insert(
						std::pair<unsigned int, Location*>(locId, loc));
			}
			// MOTH
			else if (type == "moth")
			{
				loc = new MothLocation(locDesc, locId, x, y);
				m_mothLocations.insert(
						std::pair<unsigned int, MothLocation*>(locId,
								static_cast<MothLocation*>(loc)));

				size_t numInvalidSecret = locationsXml.getNumTags(
						"invalid-secret");
				if (numInvalidSecret > 0)
				{
					for (size_t j = 0; j < numInvalidSecret; j++)
					{
						unsigned int inv;
						std::stringstream invSs;
						invSs << locationsXml.getValue("link-blocked", "0", j);
						invSs >> inv;

						static_cast<MothLocation*>(loc)->addInvalidSecret(inv);
					}
				}
			}
			// OBSTACLE
			else if (type == "obstacle")
			{
				std::stringstream skillNeedSS;
				skillNeedSS << locationsXml.getValue("solve", "ERROR_NO_SOLVE");
				unsigned int skillNeedId;
				skillNeedSS >> skillNeedId;

				std::stringstream skillGiveSS;
				skillGiveSS << locationsXml.getValue("skill", "ERROR_NO_SKILL");
				unsigned int skillGiveId;
				skillGiveSS >> skillGiveId;

				loc = new ObstacleLocation(locDesc, locId, skillNeedId,
						skillGiveId, x, y);
				m_obstacleLocations.insert(
						std::pair<unsigned int, ObstacleLocation*>(locId,
								static_cast<ObstacleLocation*>(loc)));

				size_t numBlockedLinks = locationsXml.getNumTags(
						"link-blocked");
				if (numBlockedLinks > 0)
				{
					for (size_t j = 0; j < numBlockedLinks; j++)
					{
						unsigned int linkId;
						std::stringstream linkIdSs;
						linkIdSs
								<< locationsXml.getValue("link-blocked", "0",
										j);
						linkIdSs >> linkId;

						static_cast<ObstacleLocation*>(loc)->addBlockedLink(
								linkId);
					}
				}

			}
			else
			{
				ofLog(OF_LOG_ERROR)
						<< "[ERROR] - invalid type for location from xml";
			}

			if (numLinks > 0)
			{
				for (size_t j = 0; j < numLinks; j++)
				{
					unsigned int linkId;
					std::stringstream linkIdSs;
					linkIdSs << locationsXml.getValue("link", "0", j);
					linkIdSs >> linkId;

					loc->addLink(linkId);
				}
			}

			if (numNodes > 0)
			{
				for (int j = 0; j < numNodes; j++)
				{

					locationsXml.pushTag("node", j);
					std::stringstream nodeStream;
					unsigned int nodeId;
					std::string nodeTxt;

					nodeTxt = locationsXml.getValue("text", "");
					nodeStream << locationsXml.getValue("id", "0");
					nodeStream >> nodeId;

					nodeStream = std::stringstream();

					StoryNode* node = new StoryNode(nodeId, nodeTxt);

					int numResponses = locationsXml.getNumTags("response");

					for (int k = 0; k < numResponses; k++)
					{

						locationsXml.pushTag("response", k);

						// type
						std::string resTypeStr;
						RESPONSE resType;
						// id
						std::stringstream resStream;
						unsigned int resId;
						// text
						std::string resTxt;
						// skill
						std::string resSkillStr;
						unsigned int resSkill;
						std::stringstream resSkillSS;
						// threshold
						int resThresh;
						// description
						std::string resDesc;

						resTypeStr = locationsXml.getValue("type",
								"[ERROR] - no response type from xml");
						if (resTypeStr == "normal")
						{
							resType = RESPONSE_NORMAL;
							resStream = std::stringstream();
							resStream
									<< locationsXml.getValue("id",
											"[ERROR] - no response id from xml");
							resStream >> resId;
							resTxt = locationsXml.getValue("text",
									"[ERROR] - no response text from xml");

							node->addResponse(resType, resId, resTxt);

						}
						else if (resTypeStr == "secret")
						{
							resType = RESPONSE_SECRET;
							resStream = std::stringstream();
							resStream
									<< locationsXml.getValue("id",
											"[ERROR] - no response id from xml");
							resStream >> resId;
							resTxt = locationsXml.getValue("text",
									"[ERROR] - no response text from xml");

							resStream = std::stringstream();
							resStream
									<< locationsXml.getValue("threshold",
											"[ERROR] - no response threshold from xml");

							resStream >> resThresh;

							node->addResponse(resType, resId, resTxt,
									resThresh);
						}
						else if (resTypeStr == "teach")
						{
							resType = RESPONSE_TEACH;

							resTxt = locationsXml.getValue("text",
									"[ERROR] - no response text from xml");

							resStream = std::stringstream();
							resStream
									<< locationsXml.getValue("threshold",
											"[ERROR] - no response threshold from xml");

							resStream >> resThresh;

							resDesc = locationsXml.getValue("description",
									"[ERROR] - No response description in xml");

							resSkillSS
									<< locationsXml.getValue("skill",
											"[ERROR] - No response skill in xml");
							resSkillSS >> resSkill;

							node->addResponse(resType, resId, resTxt, resThresh,
									resSkill);
						}

						locationsXml.popTag();

					}

					loc->addStoryNode(node->getID(), *node);
					locationsXml.popTag();

				}
			}

			m_allLocations.insert(
					std::pair<unsigned int, Location*>(locId, loc));
			locationsXml.popTag();
		}

	}

	allLocationsLoaded = true;
}

ofTrueTypeFont& DataLoader::getFont(FONT_SIZE _sz)
{
	return fonts.find(_sz)->second;
}

void DataLoader::update()
{
	if (!allFontsLoaded)
	{
		allFontsLoaded = true;
		for (iFont it = fonts.begin(); it != fonts.end(); it++)
		{
			if (!it->second.isLoaded())
			{
				allFontsLoaded = false;
			}
		}
	}
}

bool DataLoader::areFontsLoaded()
{
	return allFontsLoaded;
}

bool DataLoader::areLocationsLoaded()
{
	return allLocationsLoaded;
}

} /* namespace moth */
