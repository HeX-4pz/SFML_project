#include <iostream>

#include "PlayerController.h"
#include "Spaceship.h"
#include "Command.h"


struct PlayerMover
{
    PlayerMover(float vx, float vy) : mVelocity(vx, vy) {}

    void operator ()(SceneNode& node, sf::Time dTime);

    sf::Vector2f mVelocity;
};

Command playerAction(PlayerMover mover)
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
    float speed = 300;

    mCommandBindings[Action::moveUp] = playerAction(PlayerMover(0.f, -speed));
    mCommandBindings[Action::moveDown] = playerAction(PlayerMover(0.f, speed));
    mCommandBindings[Action::moveLeft] = playerAction(PlayerMover(-speed, 0.f));
    mCommandBindings[Action::moveRight] = playerAction(PlayerMover(speed, 0.f));

    mCommandBindings[Action::writePos] = playerAction([](SceneNode& node, sf::Time dTime) {
        sf::Vector2f position = node.getPosition();
        std::cout << "Position [" << position.x << ", " << position.y << "]" << std::endl;
    });

    // key assign
    AssignKey(sf::Keyboard::W, Action::moveUp);
    AssignKey(sf::Keyboard::S, Action::moveDown);
    AssignKey(sf::Keyboard::A, Action::moveLeft);
    AssignKey(sf::Keyboard::D, Action::moveRight);
    AssignKey(sf::Keyboard::I, Action::writePos);
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
    case PlayerController::moveUp:
    case PlayerController::moveDown:
    case PlayerController::moveLeft:
    case PlayerController::moveRight:
        return true;
    }

    return false;
}

void PlayerMover::operator()(SceneNode& node, sf::Time dTime)
{
    Spaceship& spaceship = static_cast<Spaceship&>(node);
    spaceship.Accelerate(mVelocity);
}
