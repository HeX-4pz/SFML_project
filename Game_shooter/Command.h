#pragma once
#include <queue>
#include <functional>
#include <SFML/Graphics.hpp>

class SceneNode;

enum CommandType
{
    CommandType_None =              0,
    CommandType_Scene =             1 << 0,
    CommandType_Pawn =              1 << 1,
    CommandType_PlayerSpaceship =   1 << 2,
    CommandType_FrendlySpaceship =  1 << 3,
    CommandType_EnemySpaceship =    1 << 4,
};

struct Command
{
    std::function<void(SceneNode&, sf::Time)> mAction;
    unsigned int mCommandType;
};

class QueueInputCommands
{
public:
    void push(Command& event);
    Command pop();
    bool empty() const;

private:
    std::queue<Command> mEvents;
};

