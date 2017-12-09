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
		CONFIG_DIR("config"), CONFIG_NAME("config.cfg"), LOCATION_DIR(
				"locations"), LOCATION_NAME("locations.xml")
{
	fontHeaderFound = false;
	fonts.insert(fontPair(FONT_SMALL, ofTrueTypeFont()));
	fonts.insert(fontPair(FONT_MEDIUM, ofTrueTypeFont()));
	fonts.insert(fontPair(FONT_LARGE, ofTrueTypeFont()));
	allFontsLoaded = false;

	allLocationsLoaded = false;

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

std::vector<Location*> DataLoader::getLocations()
{
	return locations;
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

			locationsXml.pushTag("location", i);
			int numNodes = locationsXml.getNumTags("node");

			Location* loc = new Location();

			if (numNodes > 0)
			{
				for (int j = 0; j < numNodes; j++)
				{
					ofLog(OF_LOG_VERBOSE)
							<< "[DataLoader] Loading node number: " << j;

					locationsXml.pushTag("node", j);
					std::stringstream nodeStream;
					unsigned int nodeId;
					std::string nodeTxt;

					nodeTxt = locationsXml.getValue("text", "");
					nodeStream << locationsXml.getValue("id", "0");
					nodeStream >> nodeId;

					ofLog(OF_LOG_VERBOSE) << "[DataLoader] Node Info, Text: "
							<< nodeTxt << " ID: " << nodeId;

					StoryNode* node = new StoryNode(nodeId, nodeTxt);

					int numResponses = locationsXml.getNumTags("response");

					for (int k = 0; k < numResponses; k++)
					{
						ofLog(OF_LOG_VERBOSE)
								<< "[DataLoader] Loading response number: "
								<< k;

						locationsXml.pushTag("response", k);

						std::stringstream resStream;
						unsigned int resId;
						std::string resTxt;

						resTxt = locationsXml.getValue("text", "");
						resStream << locationsXml.getValue("id", "0");
						resStream >> resId;

						ofLog(OF_LOG_VERBOSE)
								<< "[DataLoader] Response info, Text: " << resTxt
								<< " ID: " << resId;

						node->addResponse(resId, resTxt);
						locationsXml.popTag();

					}

					loc->addStoryNode(node->getID(), node);
					locationsXml.popTag();

				}
			}

			locations.push_back(loc);
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
