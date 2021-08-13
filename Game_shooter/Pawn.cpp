#include "Pawn.h"

Pawn::Pawn()
{
    SetVelocity(0, 0);
}

void Pawn::SetVelocity(sf::Vector2f velocity)
{
    SetVelocity(velocity.x, velocity.y);
}

void Pawn::SetVelocity(float x, float y)
{
    mVelocity.x = x;
    mVelocity.y = y;
}

sf::Vector2f Pawn::GetVelocity()
{
    return mVelocity;
}

void Pawn::UpdateCurent(sf::Time dTime)
{
    move(mVelocity * dTime.asSeconds());
}
