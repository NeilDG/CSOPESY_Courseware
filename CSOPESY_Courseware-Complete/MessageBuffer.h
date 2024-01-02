#pragma once
#include <sstream>
#include <vector>

#include "TypedefRepo.h"
/**
 * \brief Class for storing messages. Once print is called, it flushes the message buffer.
 */
class MessageBuffer
{
public:
	static void initialize();
	static void destroy();

	static void log(String message);
	static void log(std::stringstream message);
	static bool hasBacklogMessages();
	static void printBacklogMessages();

private:
	MessageBuffer() = default;
	~MessageBuffer() = default;
	MessageBuffer(MessageBuffer const&) {}; // copy constructor is private
	MessageBuffer& operator=(MessageBuffer const&) {}; // assignment operator is private*/
	static MessageBuffer* sharedInstance;

	std::vector<String> backlogMessages;
};

