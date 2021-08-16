#pragma once
#include "Pawn.h"
#include "ResourceHolder.hpp"

class World;

class Spaceship :
    public Pawn
{
public:
    enum Type
    {
        Eagle,
        Raptor,
    };
private:

public:
    explicit Spaceship(Type type, World& world, const TexturesHolder& textures);
    virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    
    void SetSpeedLimits(sf::Vector2f limit);
    const sf::Vector2f GetSpeedLimits() const;

protected:
    World& mWorld;
    sf::Vector2f mSpeedLimits;

private:
    Type mType;
    sf::Sprite mSprite;
    

};

