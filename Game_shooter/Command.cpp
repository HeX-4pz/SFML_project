#include "Command.h"
#include "SceneNode.h"

void QueueInputCommands::push(Command & event)
{
    mEvents.push(event);
}

Command QueueInputCommands::pop()
{
    Command command = mEvents.front();
    mEvents.pop();
    return command;
}

bool QueueInputCommands::empty() const
{
    return mEvents.empty();
}
