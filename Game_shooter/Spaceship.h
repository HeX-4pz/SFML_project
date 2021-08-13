#pragma once
#include "Pawn.h"
#include "ResourceHolder.hpp"

class Spaceship :
    public Pawn
{
public:
    enum Type
    {
        Eagle,
        Raptor,
    };

public:
    explicit Spaceship(Type type, const TexturesHolder& textures);
    virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    
    void SetSpeedLimits(sf::Vector2f limit);
    const sf::Vector2f GetSpeedLimits() const;

private:
    Type mType;
    sf::Sprite mSprite;

    sf::Vector2f mSpeedLimits;

};

