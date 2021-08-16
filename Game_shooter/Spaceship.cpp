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

Spaceship::Spaceship(Type type, World& world, const TexturesHolder & textures) : mSpeedLimits(), mWorld(world)
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

void Spaceship::SetSpeedLimits(sf::Vector2f limit)
{
    mSpeedLimits = limit;
}

const sf::Vector2f Spaceship::GetSpeedLimits() const
{
    return mSpeedLimits;
}

