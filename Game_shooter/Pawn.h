#pragma once
#include <SFML/Graphics.hpp>
#include "SceneNode.h"

class Pawn :
    public SceneNode
{
public:
    Pawn();
    void SetVelocity(sf::Vector2f velocity);
    void SetVelocity(float x, float y);

    void Accelerate(sf::Vector2f dVelocity);
    void Accelerate(float dx, float dy);

    sf::Vector2f GetVelocity();

private:
    virtual void UpdateCurent(sf::Time dTime);

    CommandType GetCommandType() { return CommandType_Pawn; };

protected:
    sf::Vector2f mVelocity;
};

