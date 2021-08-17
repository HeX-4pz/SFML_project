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
    CommandType GetCommandType() override;

public:
    explicit Spaceship(Type type, World& world, const TexturesHolder& textures);
    virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    
protected:
    World& mWorld;

private:
    Type mType;
    sf::Sprite mSprite;
    

};

