#include "MessageBuffer.h"

#include <iostream>

MessageBuffer* MessageBuffer::sharedInstance = nullptr;
void MessageBuffer::initialize()
{
	sharedInstance = new MessageBuffer();
}

void MessageBuffer::destroy()
{
	delete sharedInstance;
}

/**
 * \brief Message to store in buffer. Automatically adds a new line.
 * \param message Message to store in buffer. Automatically adds a new line.
 */
void MessageBuffer::log(String message)
{
	// sharedInstance->backlogMessages.push_back(message);
}

void MessageBuffer::log(std::stringstream message)
{
	sharedInstance->log(message.str());
}

bool MessageBuffer::hasBacklogMessages()
{
	return sharedInstance->backlogMessages.size() > 0;
}

void MessageBuffer::printBacklogMessages()
{
	for(int i = 0; i < sharedInstance->backlogMessages.size(); i++)
	{
		std::cout << sharedInstance->backlogMessages[i];
	}

	sharedInstance->backlogMessages.clear();
}
