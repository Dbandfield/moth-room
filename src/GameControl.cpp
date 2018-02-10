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

	hunger = 100;
	humanity = 100;

	currentLocationType = LOCATION_NORMAL;
	m_audioPlayer = nullptr;
	currentNode = 0;
	displayControl = nullptr;
}

GameControl::~GameControl()
{
}

void GameControl::setAudioPlayer(AudioPlayer* _player)
{
	m_audioPlayer = _player;
}

void GameControl::tellSecret(Args _arg)
{
	displayControl->clearContent(AREA_MAIN);
	displayControl->clearLayout(AREA_MAIN);
	displayControl->clearContent(AREA_BUTTONS);
	displayControl->clearLayout(AREA_BUTTONS);
	std::vector<float> layout;

	layout.push_back(100.f);
	layout.push_back(100.f);
	layout.push_back(100.f);
	layout.push_back(100.f);

	displayControl->setLayout(AREA_MAIN, layout);

	std::string txt = "";

	Secret* sec = m_allSecrets[_arg[0]];
	MajorMothLocation* mothLoc;
	switch (currentLocation->getType())
	{
	case LOCATION_MAJ_MOTH:

		mothLoc = static_cast<MajorMothLocation*>(currentLocation);

		txt = "You tell the moth a secret ... ";
		displayControl->addText(AREA_MAIN, 0, txt, FONT_SMALL);

		txt = sec->getText();
		displayControl->addText(AREA_MAIN, 1, txt, FONT_SMALL);

		if (mothLoc->tellTheMothASecret(sec))
		{
			std::stringstream ss;
			ss << sec->getPower();
			txt = " ... and the moth's opinion of you changes by " + ss.str();
			displayControl->addText(AREA_MAIN, 2, txt, FONT_SMALL);
		}
		else
		{
			txt = " ... but the moth does not really care.";
			displayControl->addText(AREA_MAIN, 2, txt, FONT_SMALL);
		}

		break;

	case LOCATION_MIN_MOTH:
	case LOCATION_NORMAL:
	case LOCATION_OBSTACLE:
		txt = "No one here wants to hear your secrets.";
		displayControl->addText(AREA_MAIN, 0, txt, FONT_SMALL);
		break;
	}

	Args a1;
	a1.push_back(currentNodeID);

	displayControl->addOption(AREA_MAIN, 3, "return", &GameControl::advanceNode,
			a1, FONT_SMALL);
}

void GameControl::useSkill(Args _arg)
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

	std::string txt = "";

	Skill* skill = m_gainedSkills[_arg[0]];
	ObstacleLocation* obLoc;
	switch (currentLocation->getType())
	{
	case LOCATION_OBSTACLE:

		obLoc = static_cast<ObstacleLocation*>(currentLocation);

		txt += "You use your skill in ... ";
		txt += "\n";
		txt += skill->getText();
		txt += "\n";

		if (obLoc->solve(skill->getId()))
		{
			txt += "[REPLACE] ... and the obstacle is solved![REPLACE]";
		}
		else
		{
			txt += " ... but it dawns on you this will acheive nothing.";
		}

		break;

	case LOCATION_NORMAL:
	case LOCATION_MAJ_MOTH:
	case LOCATION_MIN_MOTH:
		txt += "This neither the time nor place to show off your skills.";
		break;
	}

	displayControl->addText(AREA_MAIN, 1, txt, FONT_SMALL);

	Args a1;
	a1.push_back(currentNodeID);

	displayControl->addOption(AREA_MAIN, 7, "return", &GameControl::advanceNode,
			a1, FONT_SMALL);
}

void GameControl::listSkills(Args _arg)
{
	displayControl->clearContent(AREA_MAIN);
	displayControl->clearLayout(AREA_MAIN);
	displayControl->clearContent(AREA_BUTTONS);
	displayControl->clearLayout(AREA_BUTTONS);
	std::vector<float> layout;

	layout.push_back(100.f);
	layout.push_back(30.f);
	layout.push_back(30.f);
	layout.push_back(30.f);
	layout.push_back(100.f);

	ofLog() << "[GAME_CONTROL] - Setting layout of skills";
	displayControl->setLayout(AREA_MAIN, layout);

	displayControl->addText(AREA_MAIN, 0, "You know how to: ", FONT_MEDIUM);

	int count = 0;
	int layoutNum = 1;

	for (auto&& it : m_gainedSkills)
	{
		std::string txt = it.second->getText();

		Args a1;
		a1.push_back(it.second->getId());

		displayControl->addOption(AREA_MAIN, layoutNum, txt,
				&GameControl::useSkill, a1, FONT_SMALL);
		count++;
		if (count > 8)
		{
			count = 0;
			layoutNum++;
		}
	}

	Args a2;
	a2.push_back(currentNodeID);

	displayControl->addOption(AREA_MAIN, 4, "return", &GameControl::advanceNode,
			a2, FONT_SMALL);

}

void GameControl::listSecrets(Args _arg)
{
	displayControl->clearContent(AREA_MAIN);
	displayControl->clearLayout(AREA_MAIN);
	displayControl->clearContent(AREA_BUTTONS);
	displayControl->clearLayout(AREA_BUTTONS);
	std::vector<float> layout;

	layout.push_back(100.f);
	layout.push_back(30.f);
	layout.push_back(30.f);
	layout.push_back(30.f);
	layout.push_back(100.f);

	ofLog() << "[GAME_CONTROL] - Setting layout of secrets";
	displayControl->setLayout(AREA_MAIN, layout);

	displayControl->addText(AREA_MAIN, 0, "[ You Know About ]", FONT_MEDIUM);

	int count = 0;
	int layoutNum = 1;

	for (auto&& it : discoveredSecrets)
	{
		std::string txt = it.second->getShort();

		Args a1;
		a1.push_back(it.second->getId());

		displayControl->addOption(AREA_MAIN, layoutNum, txt,
				&GameControl::tellSecret, a1, FONT_SMALL);

		count++;
		if (count > 8)
		{
			count = 0;
			layoutNum++;
		}
	}

	Args a2;
	a2.push_back(currentNodeID);

	displayControl->addOption(AREA_MAIN, 4, "return", &GameControl::advanceNode,
			a2, FONT_SMALL);

}

void GameControl::eat(Args _arg)
{
	hunger = std::min(hunger + 10, 100);
	humanity = std::max(humanity - 10, 0);

	displayControl->setCorruption(
			(int) (((100.f - (float) humanity) + 1.f) / 10.f));

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

	Args a1;
	a1.push_back(currentNodeID);

	displayControl->addOption(AREA_MAIN, 1, "return", &GameControl::advanceNode,
			a1, FONT_SMALL);
}

void GameControl::listLocations(Args _arg)
{
	displayControl->clearContent(AREA_MAIN);
	displayControl->clearLayout(AREA_MAIN);
	displayControl->clearContent(AREA_BUTTONS);
	displayControl->clearLayout(AREA_BUTTONS);
	std::vector<float> layout;

	layout.push_back(100.f);
	layout.push_back(100.f);
	layout.push_back(100.f);
	layout.push_back(100.f);

	ofLog() << "[GAME_CONTROL] - Setting layout of locations";

	displayControl->setLayout(AREA_MAIN, layout);
	displayControl->addText(AREA_MAIN, 0, "Fly to: ", FONT_SMALL);

	Symbol* label = displayControl->addText(AREA_MAIN, 2, "", FONT_SMALL);

	for (auto it : allLocations)
	{
		auto linkVec = it.second->getLinks();

		std::string txt = it.second->getDescription();

		Args a1;
		a1.push_back(it.first);

		ofLog() << "[GAME_CONTROL] - adding map option";
		displayControl->addMapOption(it.first, it.second->getRelX(),
				it.second->getRelY(), AREA_MAIN, 1, txt,
				&GameControl::moveLocation, a1, linkVec, label, FONT_SMALL);
	}

	Args a2;
	a2.push_back(currentNodeID);

	displayControl->addOption(AREA_MAIN, 3, "return", &GameControl::advanceNode,
			a2, FONT_SMALL);
}

void GameControl::setSkills(std::map<unsigned int, Skill*> _skills)
{
	m_allSkills = _skills;
}

void GameControl::learnSkill(Args _arg)
{
	std::string txt = "";

	if (knowsSkill(_arg[0]))
	{
		txt = "You already know this skill: ";
		txt += "\n";
	}
	else
	{
		if (likedEnoughByMoth(_arg[1]))
		{
			txt = "You learn a new skill: ";
			txt += "\n";

			m_gainedSkills.insert(
					std::pair<unsigned int, Skill*>(_arg[0],
							m_allSkills[_arg[0]]));
		}
		else
		{
			txt = "The moth does not like you enough to teach you: ";
			txt += "\n";
		}
	}

	txt += m_allSkills[_arg[0]]->getText();

	displayControl->clearContent(AREA_MAIN);
	displayControl->clearLayout(AREA_MAIN);
	displayControl->clearContent(AREA_BUTTONS);
	displayControl->clearLayout(AREA_BUTTONS);

	std::vector<float> layout;

	layout.push_back(50.f);
	layout.push_back(50.f);

	displayControl->setLayout(AREA_MAIN, layout);
	displayControl->addText(AREA_MAIN, 0, txt, FONT_SMALL);

	Args a1;
	a1.push_back(currentNodeID);

	displayControl->addOption(AREA_MAIN, 1, "return", &GameControl::advanceNode,
			a1, FONT_SMALL);
}

void GameControl::learnSecret(Args _arg)
{
	std::string txt = "";

	if (knowsSecret(_arg[0]))
	{
		txt = "You already know this secret: ";
		txt += "\n";
		txt += m_allSecrets[_arg[0]]->getText();
	}
	else
	{
		if (likedEnoughByMoth(_arg[1]))
		{
			txt = "You learn a new secret: ";
			txt += "\n";
			txt += m_allSecrets[_arg[0]]->getText();

			discoveredSecrets.insert(
					std::pair<unsigned int, Secret*>(_arg[0],
							m_allSecrets[_arg[0]]));
		}
		else
		{
			txt = "The moth does not like you enough.";
		}
	}

	displayControl->clearContent(AREA_MAIN);
	displayControl->clearLayout(AREA_MAIN);
	displayControl->clearContent(AREA_BUTTONS);
	displayControl->clearLayout(AREA_BUTTONS);

	std::vector<float> layout;

	layout.push_back(50.f);
	layout.push_back(50.f);

	displayControl->setLayout(AREA_MAIN, layout);
	displayControl->addText(AREA_MAIN, 0, txt, FONT_SMALL);

	Args a1;
	a1.push_back(currentNodeID);

	displayControl->addOption(AREA_MAIN, 1, "return", &GameControl::advanceNode,
			a1, FONT_SMALL);
}

bool GameControl::likedEnoughByMoth(unsigned int _thresh)
{
	return (static_cast<MajorMothLocation*>(currentLocation)->getOpinion()
			> _thresh);
}

void GameControl::setSecrets(std::map<unsigned int, Secret*> _secrets)
{
	discoveredSecrets = _secrets;
	m_allSecrets = _secrets;
}

bool GameControl::knowsSecret(unsigned int _secret)
{
	return discoveredSecrets.find(_secret) != discoveredSecrets.end();
}

bool GameControl::knowsSkill(unsigned int _skill)
{
	return m_gainedSkills.find(_skill) != m_gainedSkills.end();
}

void GameControl::setLocations(std::map<unsigned int, Location*> _all,
		std::map<unsigned int, MajorMothLocation*> _majMoth,
		std::map<unsigned int, MinorMothLocation*> _minMoth,
		std::map<unsigned int, ObstacleLocation*> _obstacle,
		std::map<unsigned int, Location*> _normal)
{
	allLocationsOriginal = _all;
	majMothLocationsOriginal = _majMoth;
	minMothLocationsOriginal = _minMoth;
	obstacleLocationsOriginal = _obstacle;
	normalLocationsOriginal = _normal;

	reset(std::vector<unsigned int>());

	currentLocation = allLocations[0];
	currentNodeID = 0;
	currentLocationType = currentLocation->getType();
}

void GameControl::moveLocation(Args _arg)
{
	if (makeHungry())
	{

		currentLocation = allLocations[_arg[0]];
		currentLocationType = currentLocation->getType();

		Args a1;
		a1.push_back(0);
		advanceNode(a1);
	}
}

bool GameControl::makeHungry()
{
	ofLog() << "[GAME_CONTROL] - Making Hungry from " << hunger;
	hunger = std::max(0, hunger - 5);
	ofLog() << "\t to " << hunger;
	displayControl->setLevel(LEVEL_HUNGER, hunger);

	if (hunger <= 0)
	{
		starved();
		return false;
	}
	else
	{
		return true;
	}
}

void GameControl::starved()
{
	ofLog() << "[GAME_CONTROL] - Starved";
	displayControl->clearContent(AREA_MAIN);
	displayControl->clearLayout(AREA_MAIN);
	displayControl->clearContent(AREA_BUTTONS);
	displayControl->clearLayout(AREA_BUTTONS);
	std::vector<float> layout;

	layout.push_back(100.f);
	layout.push_back(50.f);
	layout.push_back(100.f);

	displayControl->setLayout(AREA_MAIN, layout);
	displayControl->addText(AREA_MAIN, 0, "You \nDied", FONT_LARGE);
	std::string txt = "Rather than eat the fruit and succumb to life "
			"eternal as a moth, you chose to starve to death. "
			"It is unlikely the fruit-addled moths will remember you.";
	displayControl->addText(AREA_MAIN, 1, txt);

	Args a2 = Args();
	//a2.push_back(0);

	displayControl->addOption(AREA_MAIN, 2, "Actually, I want to go back.",
			&GameControl::reset, a2, FONT_SMALL);
}

void GameControl::reset(Args _arg)
{
	for (auto it : minMothLocationsOriginal)
	{
		minMothLocations.insert(
				std::make_pair(it.first, MinorMothLocation(it.second)));
		allLocations.insert(
				std::make_pair(it.first,
						&(minMothLocations.find(it.first)->second)));
	}

	for (auto it : majMothLocationsOriginal)
	{
		majMothLocations.insert(
				std::make_pair(it.first, MajorMothLocation(it.second)));
		allLocations.insert(
				std::make_pair(it.first,
						&(majMothLocations.find(it.first)->second)));
	}

	for (auto it : obstacleLocationsOriginal)
	{
		obstacleLocations.insert(
				std::make_pair(it.first, ObstacleLocation(it.second)));
		allLocations.insert(
				std::make_pair(it.first,
						&(obstacleLocations.find(it.first)->second)));
	}

	for (auto it : normalLocationsOriginal)
	{
		normalLocations.insert(std::make_pair(it.first, Location(it.second)));
		allLocations.insert(
				std::make_pair(it.first,
						&(normalLocations.find(it.first)->second)));
	}

	hunger = 100;
	humanity = 100;

	displayControl->setLevel(LEVEL_HUNGER, hunger);

	discoveredSecrets.clear();
	m_gainedSkills.clear();

	locationsReady();
}

void GameControl::advanceNode(Args _arg)
{

	if (makeHungry())
	{
		displayControl->clearContent(AREA_MAIN);
		displayControl->clearLayout(AREA_MAIN);
		displayControl->clearContent(AREA_BUTTONS);
		displayControl->clearLayout(AREA_BUTTONS);
		std::vector<float> layout;

		layout.push_back(100.f);
		if (currentLocation->getType() == LOCATION_MAJ_MOTH
				|| currentLocation->getType() == LOCATION_MIN_MOTH)
			layout.push_back(100.f);
		layout.push_back(50.f);
		layout.push_back(50.f);
		layout.push_back(50.f);
		layout.push_back(50.f);

		displayControl->setLayout(AREA_MAIN, layout);
		currentNodeID = _arg[0];
		currentNode = currentLocation->getNode(currentNodeID);

		int layoutNum = 0;

		displayControl->addText(AREA_MAIN, layoutNum,
				"[ " + currentLocation->getDescription() + " ]", FONT_MEDIUM);

		layoutNum++;

		if (currentLocation->getType() == LOCATION_MAJ_MOTH)
		{
			MajorMothLocation* moLoc = static_cast<MajorMothLocation*>(currentLocation);
			std::stringstream ss;
			ss << moLoc->getOpinion();
			displayControl->addText(AREA_MAIN, layoutNum,
					"[ likes you " + ss.str() + "% ]", FONT_SMALL);

			layoutNum++;
		}
		else if (currentLocation->getType() == LOCATION_MIN_MOTH)
		{
			MinorMothLocation* moLoc = static_cast<MinorMothLocation*>(currentLocation);
			std::stringstream ss;
			ss << moLoc->getOpinion();
			displayControl->addText(AREA_MAIN, layoutNum,
					"[ likes you " + ss.str() + "% ]", FONT_SMALL);

			layoutNum++;
		}

		displayControl->addText(AREA_MAIN, layoutNum, currentNode->getText(),
				FONT_SMALL);

		layoutNum++;

		auto res = currentNode->getResponses();

		for (auto&& it : res)
		{
			Args a1;
			std::string txt;
			std::stringstream ss1, ss2;
			switch (it->getType())
			{

			case RESPONSE_NORMAL:

				ofLog() << "REPSONSE " << it->getId();
				a1.push_back(it->getId());
				txt = it->getText();
				displayControl->addOption(AREA_MAIN, layoutNum, txt,
						&GameControl::advanceNode, a1, FONT_SMALL);
				break;

			case RESPONSE_SECRET:

				a1.push_back(it->getId());
				a1.push_back(it->getThreshold());
				ss1 << it->getThreshold();
				txt = it->getText();
				txt += " [";
				txt += ss1.str();
				txt += "%] ";

				displayControl->addOption(AREA_MAIN, layoutNum, txt,
						&GameControl::learnSecret, a1, FONT_SMALL);
				break;

			case RESPONSE_TEACH:

				a1.push_back(it->getSkill());
				a1.push_back(it->getThreshold());
				ss2 << it->getThreshold();
				txt = it->getText();
				txt += " [";
				txt += ss2.str();
				txt += "%] ";
				displayControl->addOption(AREA_MAIN, layoutNum, txt,
						&GameControl::learnSkill, a1, FONT_SMALL);

				break;
			}

		}

		setButtons();

	}
}

void GameControl::beginGame(Args _arg)
{
	ofLog(OF_LOG_VERBOSE) << "[GameControl] Beginning Game";

	Args a;
	a.push_back(0);
	advanceNode(a);

}

void GameControl::setButtons()
{
	std::vector<float> layoutButtons;
	layoutButtons.push_back(100.f);
	displayControl->setLayout(AREA_BUTTONS, layoutButtons);
	Args a1;
	a1.push_back(0);
	displayControl->addOption(AREA_BUTTONS, 0, "Eat", &GameControl::eat, a1,
			FONT_SMALL, false, true, FLOW_HORIZONTAL);
	Args a2;
	a2.push_back(currentLocation->getId());
	displayControl->addOption(AREA_BUTTONS, 0, "Go",
			&GameControl::listLocations, a2, FONT_SMALL, false, true,
			FLOW_HORIZONTAL);
	displayControl->addOption(AREA_BUTTONS, 0, "Secret",
			&GameControl::listSecrets, a1, FONT_SMALL, false, true,
			FLOW_HORIZONTAL);
	displayControl->addOption(AREA_BUTTONS, 0, "Skill",
			&GameControl::listSkills, a1, FONT_SMALL, false, true,
			FLOW_HORIZONTAL);

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
	Args a1;
	a1.push_back(0);
	displayControl->addOption(AREA_MAIN, 2, "Continue", &GameControl::beginGame,
			a1, FONT_SMALL);

//setButtons();

}

void GameControl::setDisplayControl(DisplayControl *_displayControl)
{
	ofLog(OF_LOG_VERBOSE) << "[GameControl] Setting Display Control";

	displayControl = _displayControl;

}

} /* namespace moth */
