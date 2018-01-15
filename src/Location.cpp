/*
 * Location.cpp
 *
 *  Created on: 4 Dec 2017
 *      Author: daniel
 */

#include "Location.h"

namespace moth
{

Location::Location(std::string _description, unsigned int _id)
{

	description = _description;

	id = _id;

	m_type = LOCATION_NORMAL;
}

Location::~Location()
{
	for (auto i = storyNodes.begin(); i != storyNodes.end(); i++)
	{
		delete i->second;
	}
}

LOCATION Location::getType()
{
	return m_type;
}

void Location::addLink(unsigned int _id)
{
	links.push_back(_id);
}

void Location::addStoryNode(unsigned int _ID, StoryNode* _node)
{
	ofLog() << "ADDING: " << _ID;
	storyNodes.insert(std::pair<unsigned int, StoryNode*>(_ID, _node));
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
		return storyNodes[_ID];
	}
}

} /* namespace moth */
