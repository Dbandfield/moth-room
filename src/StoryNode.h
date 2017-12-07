#pragma once

#include <string>
#include <map>

namespace moth
{

class StoryNode
{
public:
	StoryNode(unsigned int _ID, std::string _text);
	virtual ~StoryNode();

	void addResponse(unsigned int _ID, std::string _text);

	std::string getText();
	std::string getResponse(unsigned int _id);

protected:
	unsigned int ID;

	std::string text;

	/* A response has text that is displayed, as well
	 * as an ID correspindign to the Story Node it takes you
	 * to.  */
	std::map<unsigned int, std::string> responses;
};

} /* namespace moth */
