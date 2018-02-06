/*
 * Location.cpp
 *
 *  Created on: 4 Dec 2017
 *      Author: daniel
 */

#include "Location.h"

namespace moth
{

Location::Location(Location* _loc)
{
	m_type = _loc->getType();
	description = _loc->description;
	id = _loc->id;
	links = _loc->links;
	storyNodes = _loc->storyNodes;
	relX = _loc->getRelX();
	relY = _loc->getRelY();
}

Location::Location(std::string _description, unsigned int _id, float _x, float _y)
{

	description = _description;

	id = _id;

	m_type = LOCATION_NORMAL;

	relX = _x;
	relY = _y;
}

Location::~Location()
{
//	for (auto i = storyNodes.begin(); i != storyNodes.end(); i++)
//	{
//		delete i->second;
//	}
}

LOCATION Location::getType()
{
	return m_type;
}

void Location::addLink(unsigned int _id)
{
	links.push_back(_id);
}

void Location::addStoryNode(unsigned int _ID, StoryNode _node)
{
	storyNodes.insert(std::pair<unsigned int, StoryNode>(_ID, _node));
}

StoryNode* Location::getNode(unsigned int _ID)
{
	if (storyNodes.find(_ID) == storyNodes.end())
	{
		ofLog(OF_LOG_ERROR) << "[ERROR][Location] No node with that ID " << _ID;
		return nullptr;
	}
	else
	{
		return &(storyNodes.find(_ID)->second);
	}
}

} /* namespace moth */
