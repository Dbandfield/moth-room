/*
 * StoryNode.cpp
 *
 *  Created on: 4 Dec 2017
 *      Author: daniel
 */

#include "StoryNode.h"

namespace moth
{

StoryNode::StoryNode(unsigned int _ID, std::string _text)
{
	ID = _ID;
	text = _text;
}

StoryNode::~StoryNode()
{
}

void StoryNode::addResponse(unsigned int _ID, std::string _text)
{
	responses.insert(std::pair<unsigned int, std::string>(_ID, _text));
}

std::string StoryNode::getText()
{
	return text;
}
std::string StoryNode::getResponse(unsigned int _ID)
{
	if(responses.find(_ID) == responses.end())
	{
		return "[ERROR - NO RESPONSE WITH THAT ID]";
	}
	else
	{
		return responses[_ID];
	}
}

} /* namespace moth */
