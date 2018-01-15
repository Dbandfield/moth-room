/*
 * StoryNode.cpp
 *
 *  Created on: 4 Dec 2017
 *      Author: daniel
 */

#include "StoryNode.h"

namespace moth
{

StoryNode::StoryNode(unsigned int _ID, std::string _text, bool _isSecret)
{
	ID = _ID;
	text = _text;

}

StoryNode::~StoryNode()
{
}

void StoryNode::addResponse(RESPONSE _type, unsigned int _ID, std::string _text,
		int _threshold, unsigned int _skill, std::string _desc)
{
	Response* res = new Response(_type, _ID, _text, _threshold, _skill, _desc);
	responses.push_back(res);
}

std::string StoryNode::getText()
{
	return text;
}

} /* namespace moth */
