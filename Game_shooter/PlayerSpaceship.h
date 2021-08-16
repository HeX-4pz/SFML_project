#pragma once
#include "Spaceship.h"
#include "InputController.h"

class PlayerSpaceship :
    public Spaceship,
    public InputController
{


public:
    explicit PlayerSpaceship(Type type, World& world, const TexturesHolder& textures);
    void HandleInput() override;

private:
    void UpdateCurent(sf::Time dTime) override;
};

