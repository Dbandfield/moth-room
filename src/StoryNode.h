#pragma once

#include <string>
#include <vector>

#include "Secret.h"
#include "Response.h"

namespace moth
{
typedef std::vector<Response*> vResponse;
class StoryNode
{
public:
	StoryNode(unsigned int _ID, std::string _text, bool _isSecret = false);
	virtual ~StoryNode();

	void addResponse(RESPONSE _type, unsigned int _ID, std::string _text, int _threshold=0,
			unsigned int _skill=0, std::string _desc="");

	std::string getText();
	vResponse getResponses()
	{
		return responses;
	}
	;
	unsigned int getID()
	{
		return ID;
	}
	;

protected:
	unsigned int ID;

	std::string text;

	/* A response has text that is displayed, as well
	 * as an ID correspindign to the Story Node it takes you
	 * to.  */
	vResponse responses;
};

} /* namespace moth */
