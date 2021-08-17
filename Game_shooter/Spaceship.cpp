#include "Spaceship.h"
#include "World.h"

Textures::ID ToTextureID(Spaceship::Type type) 
{
    switch (type)
    {
    case Spaceship::Eagle:
        return Textures::Spaceship_Eagle;
    case Spaceship::Raptor:
        return Textures::Spaceship_Raptor;
    }
}

CommandType Spaceship::GetCommandType()
{
    if (mType == Eagle)
        return CommandType_PlayerSpaceship;
    else if (mType == Raptor)
        return CommandType_FrendlySpaceship;

    return CommandType_EnemySpaceship;
}

Spaceship::Spaceship(Type type, World& world, const TexturesHolder & textures) : mWorld(world)
{
    mType = type;
    mSprite.setTexture(textures.Get(ToTextureID(type)));

    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Spaceship::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}


