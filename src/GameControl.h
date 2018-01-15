#pragma once

#include <vector>
#include <algorithm>

#include "DisplayControl.h"
#include "enums.h"
#include "StoryNode.h"
#include "Location.h"
#include "DataLoader.h"
#include "Secret.h"
#include "Skill.h"

namespace moth
{

class DisplayControl;

class GameControl
{
public:
	GameControl();
	virtual ~GameControl();

	void setDisplayControl(DisplayControl *_displayControl);

	void beginGame(Args _arg);
	void advanceNode(Args _arg);

	void listLocations(Args _arg);
	void listSecrets(Args _arg);
	void listSkills(Args _arg);

	void moveLocation(Args _arg);
	void tellSecret(Args _arg);
	void useSkill(Args _arg);
	void eat(Args _arg);
	void learnSecret(Args _arg);
	void learnSkill(Args _arg);

	void setLocations(std::map<unsigned int, Location*> _all,
			std::map<unsigned int, MothLocation*> _moth,
			std::map<unsigned int, ObstacleLocation*> _obstacle,
			std::map<unsigned int, Location*> _normal);

	void setSecrets(std::map<unsigned int, Secret*> _secrets);
	void setSkills(std::map<unsigned int, Skill*> _skills);

	void locationsReady();
	void secretsReady();

protected:
	void switchStage(STAGE _stage);
	void setButtons();
	void makeHungry();
	bool knowsSecret(unsigned int _secret);
	bool likedEnoughByMoth(unsigned int _thresh);
	bool knowsSkill(unsigned int _skill);


	std::map<unsigned int, Location*> allLocations;
	std::map<unsigned int, MothLocation*> mothLocations;
	std::map<unsigned int, ObstacleLocation*> obstacleLocations;
	std::map<unsigned int, Location*> normalLocations;

	Location* currentLocation;
	LOCATION currentLocationType;
	unsigned int currentNodeID;
	StoryNode* currentNode;

	DisplayControl *displayControl;
	STAGE stage;

	std::map<unsigned int, Secret*> m_allSecrets;
	std::map<unsigned int, Secret*> discoveredSecrets;
	std::map<unsigned int, Skill*> m_allSkills;
	std::map<unsigned int, Skill*> m_gainedSkills;

	int hunger;
	int humanity;

};

} /* namespace moth */
