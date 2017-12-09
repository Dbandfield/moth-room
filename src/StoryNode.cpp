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
	responses.push_back(std::pair<unsigned int, std::string>(_ID, _text));
}

std::string StoryNode::getText()
{
	return text;
}

} /* namespace moth */
