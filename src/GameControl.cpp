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

	hunger = 0;
}

GameControl::~GameControl()
{
}

void GameControl::tellSecret(unsigned int _arg)
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

	std::string txt;
	std::string res;

	bool success = currentLocation->solveProblem(_arg);

	if(success)
	{
		txt = currentLocation->getGoodSecretResponse();
		res = "Wonderful";

		displayControl->addText(0, txt, FONT_SMALL);
		displayControl->addOption(1, res, &GameControl::advanceSecretNode, currentNodeID,
				FONT_SMALL, true);

	}
	else
	{
		txt = currentLocation->getBadSecretResponse();
		res = "Unfortunate";

		displayControl->addText(0, txt, FONT_SMALL);
		displayControl->addOption(1, res, &GameControl::advanceNode, currentNodeID,
				FONT_SMALL);
	}
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
	for (auto it = discoveredSecrets.begin(); it != discoveredSecrets.end();
			it++)
	{
		std::string txt = (*it)->getText();
		displayControl->addOption(4, txt, &GameControl::tellSecret, (*it)->getId(),  FONT_SMALL);
	}

	displayControl->addOption(7, "return", &GameControl::advanceNode,
			currentNodeID, FONT_SMALL);

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

	displayControl->addOption(7, "return", &GameControl::advanceNode,
			currentNodeID, FONT_SMALL);
}

void GameControl::setLocations(std::map<unsigned int, Location*> _locs)
{
	locations = _locs;
	currentLocation = locations[0];
	currentNodeID = 0;
}

void GameControl::moveLocation(unsigned int _arg)
{
	hunger ++;
	if(animCorruptCharacter!= nullptr)
	{
		animCorruptCharacter->lock();
		int arr[1] = {hunger};
		animCorruptCharacter->setArg(arr, 1);
		animCorruptCharacter->unlock();
	}
	currentLocation = locations[_arg];
	advanceNode(0);
}

void GameControl::advanceSecretNode(unsigned int _arg)
{
	if (!currentLocation->getSecretDiscovered())
	{
		discoveredSecrets.push_back(currentLocation->getSecret());
		currentLocation->setSecretDiscovered(true);
	}

	displayControl->clearOptions();
	displayControl->clearText();
	displayControl->clearLayout();
	std::vector<float> layout;

	layout.push_back(100.f);

	layout.push_back(30.f);
	layout.push_back(30.f); // 2
	layout.push_back(30.f);

	layout.push_back(30.f);
	layout.push_back(30.f); // 5
	layout.push_back(30.f);

	displayControl->setLayout(layout);

	displayControl->addText(0, "You have gained new KNOWLEDGE:", FONT_MEDIUM);

	std::string txt = discoveredSecrets.back()->getText();
	displayControl->addText(2, txt, FONT_SMALL);

	displayControl->addOption(5, "return", &GameControl::advanceNode, _arg,
			FONT_SMALL);
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
			displayControl->addOption(1, it->second,
					&GameControl::advanceSecretNode, it->first, FONT_SMALL,
					true);
		}
		else
		{
			displayControl->addOption(1, it->second, &GameControl::advanceNode,
					it->first, FONT_SMALL);
		}
	}

	displayControl->addOption(1, "* Move to location *",
			&GameControl::listLocations, currentLocation->getId(), FONT_SMALL);
	displayControl->addOption(1, "* Tell Secret *", &GameControl::listSecrets,
			0, FONT_SMALL);

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
			"You awake in a strange place, your body aching, surrounded by darkness.\n\n\n"
			"You smell the sickly sweet scent of rotting fruit, which you can't help but find intoxicating.\n\n\n"
			"At first you think you are alone, but you begin to hear hundreds of flickerings and flutterings"
					" emerging from the darkness.", FONT_SMALL);
	displayControl->addOption(2, "Continue", &GameControl::beginGame,
			FONT_SMALL);
}

void GameControl::setDisplayControl(DisplayControl *_displayControl)
{
	ofLog(OF_LOG_VERBOSE) << "[GameControl] Setting Display Control";

	displayControl = _displayControl;
	animCorruptCharacter = new AnimCorruptCharacter();
	int iArr[1] = {0};
	animCorruptCharacter->init(iArr, 1);
	displayControl->setAnimator(animCorruptCharacter);
	displayControl->startAnimator();

}

void GameControl::switchStage(STAGE _stage)
{
	ofLog(OF_LOG_VERBOSE) << "[GameControl] Switch Stage";

	stage = _stage;
}

} /* namespace moth */
