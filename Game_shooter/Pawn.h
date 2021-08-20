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

    void Accelerate(float dv);

    void SetAngularVelocity(float vf);
    void AngularAccelerate(float df);

    sf::Vector2f GetVelocity();

private:
    virtual void UpdateCurent(sf::Time dTime);

    CommandType GetCommandType() { return CommandType_Pawn; };

protected:
    float mAngular;

    sf::Vector2f mVelocity;
    float mAngularVelocity;
};

