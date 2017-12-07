#pragma once

#include <vector>

#include "DisplayControl.h"
#include "enums.h"
#include "StoryNode.h"
#include "Location.h"

namespace moth
{

class DisplayControl;

class GameControl
{
public:
	GameControl();
	virtual ~GameControl();

	void setDisplayControl(DisplayControl *_displayControl);

	void beginGame();
	void nodeResponse();

protected:
	void switchStage(STAGE _stage);
	void makeLocations();
	void setupLocation();

	std::vector<Location*> locations;
	Location* currentLocation;
	unsigned int currentNodeID;

	DisplayControl *displayControl;
	STAGE stage;
};

} /* namespace moth */
