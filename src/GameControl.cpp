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

	hunger = 100;
	humanity = 100;
}

GameControl::~GameControl()
{
}

void GameControl::tellSecret(unsigned int _arg)
{
	displayControl->clearContent(AREA_MAIN);
	displayControl->clearLayout(AREA_MAIN);
	displayControl->clearContent(AREA_BUTTONS);
	displayControl->clearLayout(AREA_BUTTONS);
	std::vector<float> layout;

	layout.push_back(50.f);
	layout.push_back(50.f);
	layout.push_back(50.f);
	layout.push_back(50.f);

	displayControl->setLayout(AREA_MAIN, layout);

	std::string txt;
	std::string res;

	bool success = currentLocation->solveProblem(_arg);

	if (success)
	{
		txt = currentLocation->getGoodSecretResponse();
		res = "Wonderful";

		displayControl->addText(AREA_MAIN, 0, txt, FONT_SMALL);
		displayControl->addOption(AREA_MAIN, 1, res,
				&GameControl::advanceSecretNode, currentNodeID, FONT_SMALL,
				true);

	}
	else
	{
		txt = currentLocation->getBadSecretResponse();
		res = "Unfortunate";

		displayControl->addText(AREA_MAIN, 0, txt, FONT_SMALL);
		displayControl->addOption(AREA_MAIN, 1, res, &GameControl::advanceNode,
				currentNodeID, FONT_SMALL);
	}
}

void GameControl::listSecrets(unsigned int _arg)
{
	displayControl->clearContent(AREA_MAIN);
	displayControl->clearLayout(AREA_MAIN);
	displayControl->clearContent(AREA_BUTTONS);
	displayControl->clearLayout(AREA_BUTTONS);
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
	displayControl->setLayout(AREA_MAIN, layout);

	displayControl->addText(AREA_MAIN, 1, "You Know: ", FONT_MEDIUM);
	for (auto it = discoveredSecrets.begin(); it != discoveredSecrets.end();
			it++)
	{
		std::string txt = (*it)->getText();
		displayControl->addOption(AREA_MAIN, 4, txt, &GameControl::tellSecret,
				(*it)->getId(), FONT_SMALL);
	}

	displayControl->addOption(AREA_MAIN, 7, "return", &GameControl::advanceNode,
			currentNodeID, FONT_SMALL);

}

void GameControl::eat(unsigned int _arg)
{
	hunger = std::min(hunger + 10, 100);
	humanity = std::max(humanity - 10, 0);

	displayControl->setCorruption((int)(((100.f - (float)humanity) + 1.f) /10.f));

	displayControl->setLevel(LEVEL_HUNGER, hunger);
	displayControl->setLevel(LEVEL_HUMANITY, humanity);


	displayControl->clearContent(AREA_MAIN);
	displayControl->clearLayout(AREA_MAIN);
	displayControl->clearContent(AREA_BUTTONS);
	displayControl->clearLayout(AREA_BUTTONS);
	std::vector<float> layout;

	layout.push_back(50.f);
	layout.push_back(50.f);

	std::vector<std::string> fruits =
	{ "a banana", "an apple", "a pear", "a cherry", "an orange",
			"a pomegranate", "a melon" };
	std::random_shuffle(fruits.begin(), fruits.end());
	std::string txt = "You hop over to the decomposing remains of " + fruits[0]
			+ " and eat its sweet flesh. You feel satiated, "
					"but you find it harder to speak and understand "
					"human language ...";

	displayControl->setLayout(AREA_MAIN, layout);
	displayControl->addText(AREA_MAIN, 0, txt, FONT_SMALL);

	displayControl->addOption(AREA_MAIN, 1, "return", &GameControl::advanceNode,
			currentNodeID, FONT_SMALL);
}

void GameControl::listLocations(unsigned int _arg)
{
	displayControl->clearContent(AREA_MAIN);
	displayControl->clearLayout(AREA_MAIN);
	displayControl->clearContent(AREA_BUTTONS);
	displayControl->clearLayout(AREA_BUTTONS);
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

	displayControl->setLayout(AREA_MAIN, layout);
	displayControl->addText(AREA_MAIN, 1, "Fly to: ", FONT_MEDIUM);
	auto linkVec = currentLocation->getLinks();
	for (auto it = linkVec.begin(); it != linkVec.end(); it++)
	{
		std::string txt = locations[*it]->getDescription();
		displayControl->addOption(AREA_MAIN, 4, txt, &GameControl::moveLocation,
				*it, FONT_SMALL);
	}

	displayControl->addOption(AREA_MAIN, 7, "return", &GameControl::advanceNode,
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
	makeHungry();

	currentLocation = locations[_arg];
	advanceNode(0);
}

void GameControl::advanceSecretNode(unsigned int _arg)
{
	makeHungry();

	if (!currentLocation->getSecretDiscovered())
	{
		discoveredSecrets.push_back(currentLocation->getSecret());
		currentLocation->setSecretDiscovered(true);
	}

	displayControl->clearContent(AREA_MAIN);
	displayControl->clearLayout(AREA_MAIN);
	displayControl->clearContent(AREA_BUTTONS);
	displayControl->clearLayout(AREA_BUTTONS);
	std::vector<float> layout;

	layout.push_back(100.f);

	layout.push_back(30.f);
	layout.push_back(30.f); // 2
	layout.push_back(30.f);

	layout.push_back(30.f);
	layout.push_back(30.f); // 5
	layout.push_back(30.f);

	displayControl->setLayout(AREA_MAIN, layout);

	displayControl->addText(AREA_MAIN, 0, "You have gained new KNOWLEDGE:",
			FONT_MEDIUM);

	std::string txt = discoveredSecrets.back()->getText();
	displayControl->addText(AREA_MAIN, 2, txt, FONT_SMALL);

	displayControl->addOption(AREA_MAIN, 5, "return", &GameControl::advanceNode,
			_arg, FONT_SMALL);
}

void GameControl::makeHungry()
{
	hunger = std::max(0, hunger - 5);
	displayControl->setLevel(LEVEL_HUNGER, hunger);
}

void GameControl::advanceNode(unsigned int _arg)
{
	makeHungry();

	displayControl->clearContent(AREA_MAIN);
	displayControl->clearLayout(AREA_MAIN);
	displayControl->clearContent(AREA_BUTTONS);
	displayControl->clearLayout(AREA_BUTTONS);
	std::vector<float> layout;

	layout.push_back(50.f);
	layout.push_back(50.f);
	layout.push_back(50.f);
	layout.push_back(50.f);

	displayControl->setLayout(AREA_MAIN, layout);
	currentNodeID = _arg;
	currentNode = currentLocation->getNode(currentNodeID);

	displayControl->addText(AREA_MAIN, 0, currentNode->getText(), FONT_SMALL);

	auto nodeMap = currentNode->getResponses();

	for (auto it = nodeMap.begin(); it != nodeMap.end(); it++)
	{
		if (currentNode->getIsSecret())
		{
			displayControl->addOption(AREA_MAIN, 1, it->second,
					&GameControl::advanceSecretNode, it->first, FONT_SMALL,
					true);
		}
		else
		{
			displayControl->addOption(AREA_MAIN, 1, it->second,
					&GameControl::advanceNode, it->first, FONT_SMALL);
		}
	}

	setButtons();

}

void GameControl::beginGame(unsigned int _arg)
{
	ofLog(OF_LOG_VERBOSE) << "[GameControl] Beginning Game";
	switchStage(STAGE_MAIN);
	advanceNode(0);

}

void GameControl::setButtons()
{
	std::vector<float> layoutButtons;
	layoutButtons.push_back(100.f);
	displayControl->setLayout(AREA_BUTTONS, layoutButtons);
	displayControl->addOption(AREA_BUTTONS, 0, "Eat", &GameControl::eat, 0,
			FONT_SMALL, false, true, FLOW_HORIZONTAL);
	displayControl->addOption(AREA_BUTTONS, 0, "Fly somewhere",
			&GameControl::listLocations, currentLocation->getId(), FONT_SMALL,
			false, true, FLOW_HORIZONTAL);
	displayControl->addOption(AREA_BUTTONS, 0, "Reveal a secret",
			&GameControl::listSecrets, 0, FONT_SMALL, false, true, FLOW_HORIZONTAL);

}

void GameControl::locationsReady()
{
	displayControl->clearContent(AREA_MAIN);
	std::vector<float> layout;
	layout.push_back(100.f);
	layout.push_back(50.f);
	layout.push_back(50.f);
	layout.push_back(50.f);
	layout.push_back(50.f);

	displayControl->setLayout(AREA_MAIN, layout);
	displayControl->addText(AREA_MAIN, 0, "The Room of Rotting Fruit",
			FONT_LARGE);
	displayControl->addText(AREA_MAIN, 1,
			"You awake in a strange place, your body aching, surrounded by darkness.\n"
					"You smell the sickly sweet scent of rotting fruit, which you can't help but find intoxicating.\n"
					"At first you think you are alone, but you begin to hear hundreds of flutterings"
					" emerging from the darkness.", FONT_SMALL);
	displayControl->addOption(AREA_MAIN, 2, "Continue", &GameControl::beginGame,
			FONT_SMALL);

	setButtons();

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
