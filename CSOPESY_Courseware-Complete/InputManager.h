#pragma once

class InputManager
{
public:
	static InputManager* getInstance();
	static void initialize();
	static void destroy();

	static bool isKeyPressed();
	static char getPressedKey();

private:
	InputManager();
	~InputManager() = default;
	InputManager(InputManager const&) {}; // copy constructor is private
	InputManager& operator=(InputManager const&) {}; // assignment operator is private*/
	static InputManager* sharedInstance;
};

