#pragma once

#include <vector>
#include <algorithm>

#include "DisplayControl.h"
#include "enums.h"
#include "StoryNode.h"
#include "Location.h"
#include "DataLoader.h"
#include "Secret.h"

namespace moth
{

class DisplayControl;

class GameControl
{
public:
	GameControl();
	virtual ~GameControl();

	void setDisplayControl(DisplayControl *_displayControl);

	void beginGame(unsigned int _arg);
	void advanceSecretNode(unsigned int _arg);
	void advanceNode(unsigned int _arg);
	void listLocations(unsigned int _arg);
	void listSecrets(unsigned int _arg);
	void moveLocation(unsigned int _arg);
	void tellSecret(unsigned int _arg);
	void eat(unsigned int _arg);

	void setLocations(std::map<unsigned int, Location*>  _locs);
	void locationsReady();

protected:
	void switchStage(STAGE _stage);
	void setButtons();
	void makeHungry();

	std::map<unsigned int, Location*> locations;
	Location* currentLocation;
	unsigned int currentNodeID;
	StoryNode* currentNode;

	DisplayControl *displayControl;
	STAGE stage;

	std::vector<Secret*> discoveredSecrets;

	int hunger;
	int humanity;

};

} /* namespace moth */
