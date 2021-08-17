#pragma once
#include <SFML/Graphics.hpp>

class QueueInputCommands;
class SceneNode;

struct PlayerMover
{
    PlayerMover(float vx, float vy) : mVelocity(vx, vy) {}

    void operator ()(SceneNode& node, sf::Time dTime);

    sf::Vector2f mVelocity;
};

class PlayerController
{
public:
    void HandleInputEvent(sf::Event, QueueInputCommands& events);
    void HandleRealtimeInput(QueueInputCommands& events);
};

