#include <iostream>

#include "PlayerController.h"
#include "Spaceship.h"
#include "Command.h"


void PlayerController::HandleInputEvent(sf::Event event, QueueInputCommands & events)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I)
    {
        Command logPosition;
        logPosition.mCommandType = CommandType::CommandType_PlayerSpaceship;
        logPosition.mAction = [](SceneNode& node, sf::Time dTime) {
            sf::Vector2f position = node.getPosition();
            std::cout << "Position [" << position.x << ", " << position.y << "]" << std::endl;
        };

        events.push(logPosition);
    }
}

void PlayerController::HandleRealtimeInput(QueueInputCommands& events)
{
    float speed = 500;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        Command moveUp;
        moveUp.mCommandType = CommandType::CommandType_PlayerSpaceship;
        moveUp.mAction = PlayerMover(0, -speed);
        events.push(moveUp);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        Command moveDown;
        moveDown.mCommandType = CommandType::CommandType_PlayerSpaceship;
        moveDown.mAction = PlayerMover(0, speed);
        events.push(moveDown);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        Command moveLeft;
        moveLeft.mCommandType = CommandType::CommandType_PlayerSpaceship;
        moveLeft.mAction = PlayerMover(-speed, 0);
        events.push(moveLeft);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        Command moveRight;
        moveRight.mCommandType = CommandType::CommandType_PlayerSpaceship;
        moveRight.mAction = PlayerMover(speed, 0);
        events.push(moveRight);
    }
}

void PlayerMover::operator()(SceneNode& node, sf::Time dTime)
{
    Spaceship& spaceship = static_cast<Spaceship&>(node);
    spaceship.Accelerate(mVelocity);
}
