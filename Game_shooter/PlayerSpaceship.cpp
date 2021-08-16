#include "PlayerSpaceship.h"
#include "World.h"

PlayerSpaceship::PlayerSpaceship(Type type, World & world, const TexturesHolder & textures) : Spaceship(type, world, textures)
{
}

void PlayerSpaceship::HandleInput()
{
    float scroll_speed = mWorld.GetScrollSpeed();
    sf::Vector2f speed = sf::Vector2f(0, scroll_speed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        speed += sf::Vector2f(0, -mSpeedLimits.y);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        speed += sf::Vector2f(0, mSpeedLimits.y);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        speed += sf::Vector2f(-mSpeedLimits.x, 0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        speed += sf::Vector2f(mSpeedLimits.x, 0);
    }

    SetVelocity(speed);
}

void PlayerSpaceship::UpdateCurent(sf::Time dTime)
{
    HandleInput();

    sf::Vector2f nextPosition = mVelocity * dTime.asSeconds() + getPosition();
    sf::FloatRect worldBounds = mWorld.GetCurrentBouds();

    if (nextPosition.x < worldBounds.left)
        nextPosition.x = worldBounds.left;

    if (nextPosition.x > worldBounds.left + worldBounds.width)
        nextPosition.x = worldBounds.left + worldBounds.width;

    if (nextPosition.y < worldBounds.top)
        nextPosition.y = worldBounds.top;

    if (nextPosition.y > worldBounds.top + worldBounds.height)
        nextPosition.y = worldBounds.top + worldBounds.height;

    setPosition(nextPosition);
}
