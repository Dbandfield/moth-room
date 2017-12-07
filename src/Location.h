#pragma once

#include <map>
#include <string>

#include <ofMain.h>

#include "StoryNode.h"

namespace moth
{
class Location
{
public:
	Location();
	virtual ~Location();

	void addStoryNode(unsigned int _ID, StoryNode* _node);
	StoryNode* getNode(unsigned int _ID);


protected:

	std::map<unsigned int, StoryNode*> storyNodes;
	bool secretDiscovered;


};

} /* namespace moth */
