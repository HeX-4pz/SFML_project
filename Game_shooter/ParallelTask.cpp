#include "ParallelTask.h"

ParallelTask::ParallelTask()
    : mThread(&ParallelTask::RunTask, this)
    , mFinished(false)
{

}

void ParallelTask::Execute()
{
    mFinished = false;
    mElapsedTime.restart();
    mThread.launch();
}

bool ParallelTask::IsFinished()
{
    sf::Lock lock(mMutex);
    return mFinished;
}

float ParallelTask::GetCompletion()
{
    sf::Lock lock(mMutex);
    return mElapsedTime.getElapsedTime().asSeconds() / 7.f;
}

void ParallelTask::RunTask()
{
    bool ended = false;

    while (!ended)
    {
        sf::Lock lock(mMutex);
        if (mElapsedTime.getElapsedTime().asSeconds() > 7.f)
            ended = true;
    }

    {
        sf::Lock lock(mMutex);
        mFinished = true;
    }
}
