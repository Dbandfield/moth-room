/*
 * Location.cpp
 *
 *  Created on: 4 Dec 2017
 *      Author: daniel
 */

#include "Location.h"

namespace moth
{

Location::Location(std::string _description, std::string _goodSecretResponse,
		std::string _badSecretResponse, unsigned int _id,
		unsigned int _expectedSecretId, Secret *_secret)
{
	secretDiscovered = false;
	problemSolved = false;

	description = _description;
	goodSecretResponse = _goodSecretResponse;
	badSecretResponse = _badSecretResponse;

	id = _id;
	expectedSecretId = _expectedSecretId;

	secret = _secret;
}

Location::~Location()
{
	for (auto i = storyNodes.begin(); i != storyNodes.end(); i++)
	{
		delete i->second;
	}
}

bool Location::solveProblem(unsigned int _secretId)
{
	ofLog() << "Comparing " << _secretId << " to " << expectedSecretId;
	problemSolved = _secretId == expectedSecretId;
	return problemSolved;
}

void Location::setSecretDiscovered(bool _disc)
{
	secretDiscovered = _disc;
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
