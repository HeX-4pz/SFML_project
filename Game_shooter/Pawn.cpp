#include "Pawn.h"
#include <cmath>

#define PI 3.14159265  /* pi */

Pawn::Pawn():
    mAngular(0.f)
{
    SetVelocity(0, 0);
    SetAngularVelocity(0);

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

void Pawn::Accelerate(float dv)
{
    mVelocity.x -= sin(mAngular * PI / 180.f) * dv;
    mVelocity.y += cos(mAngular * PI / 180.f) * dv;
}

void Pawn::SetAngularVelocity(float vf)
{
    mAngularVelocity = vf;
}

void Pawn::AngularAccelerate(float df)
{
    mAngularVelocity += df;
}

sf::Vector2f Pawn::GetVelocity()
{
    return mVelocity;
}

void Pawn::UpdateCurent(sf::Time dTime)
{
    mAngular += mAngularVelocity * dTime.asSeconds();

    if (mAngular < 0.f)
    {
        mAngular = 360.f - mAngular;
    }
    else if(mAngular > 360.f)
    {
        mAngular = mAngular - 360.f;
    }

    setRotation(mAngular);
    move(mVelocity * dTime.asSeconds());

}
