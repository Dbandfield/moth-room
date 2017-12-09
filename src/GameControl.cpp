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

	//makeLocations();
}

GameControl::~GameControl()
{
}

void GameControl::makeLocations()
{
//	ofLog(OF_LOG_VERBOSE) << "[GameControl] Making Locations";
//
//	StoryNode* n0 = new StoryNode(0,
//			"You come across a moth awkwardly flapping it's wings"
//					"along to some unheard beat");
//	n0->addResponse(1, "Hello, can you hear music?");
//	n0->addResponse(2, "[Say Nothing, and flap your wings too]");
//
//	StoryNode* n1 =
//			new StoryNode(1,
//					"\"Oh hello. No. I can't, but there was a song I knew ... once ..."
//							"If I could only remember how it went, i would be so happy!\"");
//	n1->addResponse(3, "Fret not! I shall find you this mystery song!");
//	n1->addResponse(3, "I can't remember music either.");
//
//	StoryNode* n2 =
//			new StoryNode(2,
//					"After a while the moth notices you, and gets excited: "
//							"\"You know the song too! Do you know its name?! I have spent weeks trying to "
//							"remember it ... \"");
//	n2->addResponse(4, "I am afraid not ... ");
//	n2->addResponse(5, "Yes! I do!");
//
//	StoryNode* n3 = new StoryNode(3,
//			"The moth goes back to flapping its wings.");
//
//	StoryNode* n4 = new StoryNode(4,
//			"\"Oh... I hope some day I find it ... \"");
//	n4->addResponse(3, "Fret not! I shall find you this mystery song!");
//	n4->addResponse(3, "I can't remember music either.");
//
//	StoryNode* n5 = new StoryNode(5, "\"You do ?! What is it ?! \"");
//	n5->addResponse(4, "I Lied.");
//
//	Location* loc = new Location();
//	loc->addStoryNode(0, n0);
//	loc->addStoryNode(1, n1);
//	loc->addStoryNode(2, n2);
//	loc->addStoryNode(3, n3);
//	loc->addStoryNode(4, n4);
//	loc->addStoryNode(5, n5);
//
//	locations.push_back(loc);
	currentLocation = locations[0];
	currentNodeID = 0;

}

void GameControl::setLocations(std::vector<Location*> _locs)
{
	locations = _locs;
	currentLocation = locations[0];
	currentNodeID = 0;
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
	displayControl->addText(0,
			currentLocation->getNode(currentNodeID)->getText(), FONT_MEDIUM);
	auto nodeMap = currentLocation->getNode(currentNodeID)->getResponses();
	for (auto it = nodeMap.begin(); it != nodeMap.end(); it++)
	{
		displayControl->addOption(2,
				it->second,
				&GameControl::advanceNode, it->first, FONT_SMALL);
	}

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
			"You awake and your body feels furry; your vision segmented. ", FONT_SMALL);
	displayControl->addText(1,
					"The room is filled with the sickly sweet smell of rotting fruit, which you can't help but find intoxicating. ", FONT_SMALL);
	displayControl->addText(1, "At first you think you are alone, but as you adjust to your new eye-sight you see "
					"the darkened room is full of the flickerings and flutterings of hundreds of moths.",
			FONT_SMALL);
	displayControl->addOption(3, "Live this life ...", &GameControl::beginGame,
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
