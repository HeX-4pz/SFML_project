#pragma once
#include <map>
#include <SFML/Graphics.hpp>

class QueueInputCommands;
class Command;

class PlayerController
{
public:
    enum Action
    {
        moveUp,
        moveDown,
        moveLeft,
        moveRight,
        writePos
    };

public:
    PlayerController();

    void HandleInputEvent(sf::Event, QueueInputCommands& events);
    void HandleRealtimeInput(QueueInputCommands& events);

    void AssignKey(sf::Keyboard::Key key, Action action);

private:
    bool IsRealtimeAction(Action action);

private:
    std::map<sf::Keyboard::Key, Action> mKeyboardConnection;
    std::map<Action, Command> mCommandConnection;

};
