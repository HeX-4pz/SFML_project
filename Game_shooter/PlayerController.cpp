#include <iostream>

#include "PlayerController.h"
#include "Spaceship.h"
#include "Command.h"
#define PI 3.14159265

struct PlayerRotator
{
    PlayerRotator(float df) : mRotator(df) {}

    void operator ()(SceneNode& node, sf::Time dTime)
    {
        Spaceship& spaceship = static_cast<Spaceship&>(node);
        spaceship.AngularAccelerate(mRotator);
    }

    float mRotator;
};

struct PlayerAccelerator
{
    PlayerAccelerator(float dv) : mAccelarate(dv) {}

    void operator ()(SceneNode& node, sf::Time dTime)
    {
        Spaceship& spaceship = static_cast<Spaceship&>(node);
        spaceship.Accelerate(mAccelarate);
    }

    float mAccelarate;
};

Command playerAction(PlayerRotator mover)
{
    Command command;
    command.mCommandType = CommandType::CommandType_PlayerSpaceship;
    command.mAction = mover;

    return command;
}

Command playerAction(PlayerAccelerator mover)
{
    Command command;
    command.mCommandType = CommandType::CommandType_PlayerSpaceship;
    command.mAction = mover;

    return command;
}

Command playerAction(std::function<void(SceneNode&, sf::Time)> action)
{
    Command command;
    command.mCommandType = CommandType::CommandType_PlayerSpaceship;
    command.mAction = action;

    return command;
}

PlayerController::PlayerController()
{
    float speed = 2.f;
    float angularSpeed = 1.f;

    mCommandBindings[Action::Acceleration] = playerAction(PlayerAccelerator(-speed));
    mCommandBindings[Action::Deceleration] = playerAction(PlayerAccelerator(speed / 10.f));
    mCommandBindings[Action::Rotate—ounter—lockwise] = playerAction(PlayerRotator(-angularSpeed));
    mCommandBindings[Action::Rotate—lockwise] = playerAction(PlayerRotator(angularSpeed));

    mCommandBindings[Action::writePos] = playerAction([](SceneNode& node, sf::Time dTime) {
        sf::Vector2f position = node.getPosition();
        std::cout << "Position [" << position.x << ", " << position.y << "]" << std::endl;
    });

    mCommandBindings[Action::RestartPos] = playerAction([](SceneNode& node, sf::Time dTime) {
        Spaceship* player = dynamic_cast<Spaceship*>(&node);
        
        if (player)
        {
            player->SetVelocity(0, 0);
            player->SetAngularVelocity(0);
        }
        
    });

    // key assign
    AssignKey(sf::Keyboard::W, Action::Acceleration);
    AssignKey(sf::Keyboard::S, Action::Deceleration);
    AssignKey(sf::Keyboard::A, Action::Rotate—ounter—lockwise);
    AssignKey(sf::Keyboard::D, Action::Rotate—lockwise);
    AssignKey(sf::Keyboard::I, Action::writePos);
    AssignKey(sf::Keyboard::R, Action::RestartPos);
}

void PlayerController::HandleInputEvent(sf::Event event, QueueInputCommands & events)
{
    if (event.type == sf::Event::KeyPressed)
    {
        auto found = mKeyBindings.find(event.key.code);
        if (found != mKeyBindings.end() && !IsRealtimeAction(found->second))
        {
            events.push(mCommandBindings[found->second]);
        }
    }
}

void PlayerController::HandleRealtimeInput(QueueInputCommands& events)
{
    for (auto keyCouple : mKeyBindings)
    {
        if (IsRealtimeAction(keyCouple.second) && sf::Keyboard::isKeyPressed(keyCouple.first))
        {
            events.push(mCommandBindings[keyCouple.second]);
        }
    }
}

void PlayerController::AssignKey(sf::Keyboard::Key key, Action action)
{
    for (auto itr = mKeyBindings.begin(); itr != mKeyBindings.end();)
    {
        if (itr->second == action)
            mKeyBindings.erase(itr++);
        else
            ++itr;
    }

    mKeyBindings[key] = action;
}

bool PlayerController::IsRealtimeAction(Action action)
{
    switch (action)
    {
    case PlayerController::Acceleration:
    case PlayerController::Deceleration:
    case PlayerController::Rotate—ounter—lockwise:
    case PlayerController::Rotate—lockwise:
        return true;
    }

    return false;
}
