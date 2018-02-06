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
	Location(Location* _loc);
	Location(std::string _description, unsigned int _id, float _x, float _y);
	virtual ~Location();

	void addLink(unsigned int _id);

	void addStoryNode(unsigned int _ID, StoryNode _node);
	StoryNode* getNode(unsigned int _ID);
	unsigned int getId()
	{
		return id;
	}
	;
	inline std::vector<unsigned int> getLinks()
	{
		return links;
	};

	inline std::string getDescription()
	{
		return description;
	};

	inline float getRelX(){return relX;}
	inline float getRelY(){return relY;}

	LOCATION getType();

protected:

	LOCATION m_type;

	std::string description;
	unsigned int id;
	std::vector<unsigned int> links;

	std::map<unsigned int, StoryNode> storyNodes;

	float relX;
	float relY;

};

} /* namespace moth */
