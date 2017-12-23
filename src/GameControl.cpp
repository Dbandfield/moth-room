/*
 * GameControl.cpp
 *
 *  Created on: 2 Dec 2017
 *      Author: daniel
 */

#include "GameControl.h"

namespace moth
{

GameControl::GameControl()
{
	ofLog(OF_LOG_VERBOSE) << "[GameControl] Setup";

	switchStage(STAGE_TITLE);
}

GameControl::~GameControl()
{
}

void GameControl::listSecrets(unsigned int _arg)
{
	displayControl->clearOptions();
	displayControl->clearText();
	displayControl->clearLayout();
	std::vector<float> layout;

	layout.push_back(30.f);
	layout.push_back(30.f); // 1
	layout.push_back(30.f);

	layout.push_back(30.f);
	layout.push_back(30.f); // 4
	layout.push_back(30.f);

	layout.push_back(30.f);
	layout.push_back(30.f);  // 7
	layout.push_back(30.f);

	ofLog() << "[GAME_CONTROL] - Setting layout of secrets";
	displayControl->setLayout(layout);

	displayControl->addText(1, "You Know: ", FONT_MEDIUM);
	for (auto it = discoveredSecrets.begin(); it != discoveredSecrets.end(); it++)
	{
		std::string txt = (*it)->getText();
		displayControl->addText(4, txt,
				FONT_SMALL);
	}

	displayControl->addOption(7, "return",
			&GameControl::advanceNode, currentNodeID, FONT_SMALL);

}

void GameControl::listLocations(unsigned int _arg)
{
	displayControl->clearOptions();
	displayControl->clearText();
	displayControl->clearLayout();
	std::vector<float> layout;

	layout.push_back(30.f);
	layout.push_back(30.f); // 1
	layout.push_back(30.f);

	layout.push_back(30.f);
	layout.push_back(30.f); // 4
	layout.push_back(30.f);

	layout.push_back(30.f);
	layout.push_back(30.f);  // 7
	layout.push_back(30.f);

	ofLog() << "[GAME_CONTROL] - Setting layout of locations";

	displayControl->setLayout(layout);
	displayControl->addText(1, "Fly to: ", FONT_MEDIUM);
	auto linkVec = currentLocation->getLinks();
	for (auto it = linkVec.begin(); it != linkVec.end(); it++)
	{
		std::string txt = locations[*it]->getDescription();
		displayControl->addOption(4, txt, &GameControl::moveLocation, *it,
				FONT_SMALL);
	}

	displayControl->addOption(7, "return",
			&GameControl::advanceNode, currentNodeID, FONT_SMALL);
}

void GameControl::setLocations(std::map<unsigned int, Location*> _locs)
{
	locations = _locs;
	currentLocation = locations[0];
	currentNodeID = 0;
}

void GameControl::moveLocation(unsigned int _arg)
{
	currentLocation = locations[_arg];
	advanceNode(0);
}

void GameControl::advanceSecretNode(unsigned int _arg)
{
	ofLog() << "advance issecret!";

	discoveredSecrets.push_back(currentNode->getSecret());
	ofLog() << "add secret";
	for (auto it = discoveredSecrets.begin(); it != discoveredSecrets.end();
			it++)
	{
		discoveredSecrets[0]->getId();
		discoveredSecrets[0]->getText();


		ofLog(OF_LOG_VERBOSE) << "[GAME_CONTROL] Discovered Secret "
				<< (*it)->getId() << ": " << (*it)->getText();
	}
	advanceNode(_arg);
}

void GameControl::advanceNode(unsigned int _arg)
{
	displayControl->clearOptions();
	displayControl->clearText();
	displayControl->clearLayout();
	std::vector<float> layout;

	layout.push_back(50.f);
	layout.push_back(50.f);
	layout.push_back(50.f);
	layout.push_back(50.f);

	displayControl->setLayout(layout);
	currentNodeID = _arg;
	currentNode = currentLocation->getNode(currentNodeID);
	displayControl->addText(0, currentNode->getText(), FONT_MEDIUM);
	auto nodeMap = currentNode->getResponses();
	for (auto it = nodeMap.begin(); it != nodeMap.end(); it++)
	{
		if (currentNode->getIsSecret())
		{
			ofLog() << "issecret! " << it->second;
			displayControl->addOption(1, it->second,
					&GameControl::advanceSecretNode, it->first, FONT_SMALL);
		}
		else
		{
			displayControl->addOption(1, it->second, &GameControl::advanceNode,
					it->first, FONT_SMALL);
		}
	}

	displayControl->addOption(1, "* Move to location *",
			&GameControl::listLocations, currentLocation->getId(), FONT_SMALL);
	displayControl->addOption(1, "* Show Secrets *",
			&GameControl::listSecrets, 0, FONT_SMALL);

}

void GameControl::beginGame(unsigned int _arg)
{
	ofLog(OF_LOG_VERBOSE) << "[GameControl] Beginning Game";
	switchStage(STAGE_MAIN);
	advanceNode(0);

}

void GameControl::locationsReady()
{
	displayControl->clearOptions();
	displayControl->clearText();
	std::vector<float> layout;
	layout.push_back(100.f);
	layout.push_back(50.f);
	layout.push_back(50.f);
	layout.push_back(50.f);
	layout.push_back(50.f);

	displayControl->setLayout(layout);
	displayControl->addText(0, "The Room of Rotting Fruit", FONT_LARGE);
	displayControl->addText(1,
			"You awake in a strange place, your body aching, surrounded by darkness.",
			FONT_SMALL);
	displayControl->addText(1,
			"You smell the sickly sweet scent of rotting fruit, which you can't help but find intoxicating. ",
			FONT_SMALL);
	displayControl->addText(1,
			"At first you think you are alone, but you begin to hear hundreds of flickerings and flutterings"
					" emerging from the darkness.", FONT_SMALL);
	displayControl->addOption(2, "Continue", &GameControl::beginGame,
			FONT_SMALL);
}

void GameControl::setDisplayControl(DisplayControl *_displayControl)
{
	ofLog(OF_LOG_VERBOSE) << "[GameControl] Setting Display Control";

	displayControl = _displayControl;

}

void GameControl::switchStage(STAGE _stage)
{
	ofLog(OF_LOG_VERBOSE) << "[GameControl] Switch Stage";

	stage = _stage;
}

} /* namespace moth */
