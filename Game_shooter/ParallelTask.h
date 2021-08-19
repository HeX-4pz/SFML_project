#pragma once
#include <SFML/Graphics.hpp>

class ParallelTask
{
public:
    ParallelTask();
    
    void Execute();
    bool IsFinished();
    float GetCompletion();

private:
    void RunTask();

private:
    sf::Thread mThread;
    bool mFinished;
    sf::Clock mElapsedTime;
    sf::Mutex mMutex;
};

