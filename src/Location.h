#pragma once

#include <map>
#include <string>

#include <ofMain.h>

#include "StoryNode.h"
#include "Secret.h"

namespace moth
{
class Location
{
public:
	Location(std::string _description, std::string _goodSecretResponse,
			std::string _badSecretResponse, unsigned int _id,
			unsigned int _expectedSecretid, Secret* _secret);
	virtual ~Location();

	void addLink(unsigned int _id);

	void addStoryNode(unsigned int _ID, StoryNode* _node);
	StoryNode* getNode(unsigned int _ID);
	unsigned int getId()
	{
		return id;
	}
	;
	std::vector<unsigned int> getLinks()
	{
		return links;
	}
	;
	std::string getDescription()
	{
		return description;
	}
	;

	std::string getGoodSecretResponse()
	{
		return goodSecretResponse;
	}
	;

	std::string getBadSecretResponse()
	{
		return badSecretResponse;
	}
	;

	bool getSecretDiscovered()
	{
		return secretDiscovered;
	}
	;


	bool solveProblem(unsigned int _secretId);

	void setSecretDiscovered(bool _disc);

	Secret* getSecret(){return secret;};

protected:

	std::string badSecretResponse;
	std::string goodSecretResponse;

	std::string description;

	Secret *secret;

	unsigned int id;
	std::vector<unsigned int> links;

	std::map<unsigned int, StoryNode*> storyNodes;
	bool secretDiscovered;
	bool problemSolved;

	unsigned int expectedSecretId;

};

} /* namespace moth */
