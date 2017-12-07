/*
 * mo_font_loader.cpp
 *
 *  Created on: 20 Oct 2017
 *      Author: daniel
 */

#include "DataLoader.h"

namespace moth
{

DataLoader::DataLoader():CONFIG_DIR("config"),CONFIG_NAME("config.cfg")
{
	fontHeaderFound = false;
	fonts.insert(fontPair(FONT_SMALL, ofTrueTypeFont()));
	fonts.insert(fontPair(FONT_MEDIUM, ofTrueTypeFont()));
	fonts.insert(fontPair(FONT_LARGE, ofTrueTypeFont()));
	allLoaded = false;

}

DataLoader::~DataLoader()
{

}

void DataLoader::stripHeader(std::string &str)
{
	int openBracket = -1;
	int closeBracket = -1;

	for(size_t i = 0; i < str.size(); i ++)
	{
		if(str[i] == '[')
		{
			openBracket = i;
			break;
		}
	}

	if(openBracket == -1) return;

	for(size_t i = 0; i < str.size(); i ++)
	{
		if(str[i] == ']')
		{
			closeBracket = i;
			break;
		}
	}

	if(closeBracket == -1) return;

	str = str.substr(openBracket + 1, (closeBracket - openBracket) - 1 );
	return;

}

void DataLoader::load()
{
	// First load config
	pathToConfig = ofFilePath::join(CONFIG_DIR, CONFIG_NAME);

	if(configFile.doesFileExist(pathToConfig))
	{
		configFile.open(pathToConfig, ofFile::Mode::ReadOnly, false);
		fileBuf = configFile.readToBuffer();

		for(ofBuffer::Line it = fileBuf.getLines().begin();
				it != fileBuf.getLines().end();
				it++)
		{
			std::string line = *it;
			if(!line.empty())
			{
				if(line[0] != '#') // comments
				{
					if(line[0] == '[') // setting header
					{
						stripHeader(line);
						if(line == "fonts")
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
						if(fontHeaderFound)
						{
							std::string toFind = "font_path";
							size_t ndx1 = line.find(toFind);

							if(ndx1 != std::string::npos)
							{
								std::string equals = "=";
								size_t ndx2 = line.find(equals);
								if(ndx2 != std::string::npos)
								{
									if(ndx2 + equals.size() < line.size() - 1)
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
	else
	{
		ofLog(OF_LOG_ERROR) << "Error: Could not find config.cfg in " << pathToConfig;
		throw std::runtime_error("No config file");
	}

	ofFile *fontFileTest = new ofFile();
	fontFileTest->open(fontPath);

	if(!fontFileTest->isFile())
	{
		ofLog(OF_LOG_ERROR) << "Error: Font path not specified in " << pathToConfig;
		throw std::runtime_error("No font path specified");
	}

	delete fontFileTest;

	for(iFont it = fonts.begin(); it != fonts.end(); it ++)
	{
		if(it->first == FONT_SMALL) it->second.load(fontPath, SZ_SMALL);
		else if(it->first == FONT_MEDIUM) it->second.load(fontPath, SZ_MEDIUM);
		else if(it->first == FONT_LARGE) it->second.load(fontPath, SZ_LARGE);
	}
}

ofTrueTypeFont& DataLoader::getFont(FONT_SIZE _sz)
{
	return fonts.find(_sz)->second;
}

void DataLoader::update()
{
	if(!allLoaded)
	{
		allLoaded = true;
		for(iFont it = fonts.begin(); it != fonts.end(); it ++)
		{
			if(!it->second.isLoaded())
			{
				allLoaded = false;
			}
		}
	}
}

bool DataLoader::isLoaded()
{
	return allLoaded;
}

} /* namespace moth */
