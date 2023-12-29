#include "MarqueeWorkerThread.h"
#include "ConsoleManager.h"

MarqueeWorkerThread::MarqueeWorkerThread(int screenWidth, int screenHeight, int refreshDelay)
{
    this->isRunning = true;
    this->x = 0;
    this->y = 4;
    this->dx = 1;
    this->dy = 1;

    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->refreshDelay = refreshDelay;
}

void MarqueeWorkerThread::run()
{
    while(this->isRunning)
    {
        this->process();
        IETThread::sleep(this->refreshDelay);
    }
}

void MarqueeWorkerThread::dismiss()
{
    this->isRunning = false;
}

void MarqueeWorkerThread::process()
{
    this->move();
}

/**
 * \brief Renders the current state of the hello world position via std::cout. 
 */
void MarqueeWorkerThread::renderCurrentState() const
{
    system("cls"); // Clear screen
    ConsoleManager::getInstance()->setCursorPosition(0, 0);
    std::cout << "*****************************************" << std::endl;
    std::cout << "* Displaying a marquee console! *" << std::endl;
    std::cout << "*****************************************" << std::endl;

    ConsoleManager::getInstance()->setCursorPosition(x, y);
    std::cout << HELLO_WORLD_STRING;
}

void MarqueeWorkerThread::move()
{
    x += dx;
    y += dy;

    if (x <= 0 || x >= screenWidth - HELLO_WORLD_STRING.length())
        dx = -dx;

    if (y <= 4 || y >= screenHeight - 2)
        dy = -dy;
}
