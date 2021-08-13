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

    sf::Vector2f GetVelocity();

private:
    virtual void UpdateCurent(sf::Time dTime);

private:
    sf::Vector2f mVelocity;
};

