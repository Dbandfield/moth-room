/*
 * Location.cpp
 *
 *  Created on: 4 Dec 2017
 *      Author: daniel
 */

#include "Location.h"

namespace moth
{

Location::Location()
{

}

Location::~Location()
{
	for(auto i = storyNodes.begin(); i != storyNodes.end(); i ++)
	{
		delete i->second;
	}
}

void Location::addStoryNode(unsigned int _ID, StoryNode* _node)
{
	storyNodes.insert(std::pair<unsigned int, StoryNode*>(_ID, _node));
}

StoryNode* Location::getNode(unsigned int _ID)
{
	if(storyNodes.find(_ID) == storyNodes.end())
	{
		ofLog(OF_LOG_ERROR) << "[ERROR][Location] No node with that ID";
		return nullptr;
	}
	else
	{
		return storyNodes[_ID];
	}
}

} /* namespace moth */
