#pragma once

#include <vector>

#include "DisplayControl.h"
#include "enums.h"
#include "StoryNode.h"
#include "Location.h"
#include "DataLoader.h"

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
	void advanceNode(unsigned int _arg);
	void nodeResponse();

	void setLocations(std::vector<Location*> _locs);
	void locationsReady();

protected:
	void switchStage(STAGE _stage);
	void makeLocations();

	std::vector<Location*> locations;
	Location* currentLocation;
	unsigned int currentNodeID;

	DisplayControl *displayControl;
	STAGE stage;

};

} /* namespace moth */
