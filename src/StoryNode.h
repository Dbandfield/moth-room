#pragma once

#include <string>
#include <vector>

#include "Secret.h"

namespace moth
{
typedef std::vector<std::pair<unsigned int, std::string>> vResponse;
class StoryNode
{
public:
	StoryNode(unsigned int _ID, std::string _text, bool _isSecret=false);
	virtual ~StoryNode();

	void addResponse(unsigned int _ID, std::string _text);

	std::string getText();
	vResponse getResponses(){return responses;};
	unsigned int getID(){return ID;};
	bool getIsSecret(){return isSecret;};

protected:
	unsigned int ID;
	bool isSecret;

	std::string text;

	/* A response has text that is displayed, as well
	 * as an ID correspindign to the Story Node it takes you
	 * to.  */
	vResponse responses;
};

} /* namespace moth */
