#pragma once
#include <array>

#include <SFML/Graphics.hpp>

#include "SceneNode.h"
#include "ResourceHolder.hpp"

class Spaceship;
class QueueInputCommands;

class World : private sf::NonCopyable
{
public:
    World(sf::RenderWindow& window);

    void Update(sf::Time dTime);
    void Draw();

    sf::FloatRect GetCurrentBouds();
    float GetScrollSpeed();
    QueueInputCommands& GetCommandQueue();

private:
    void LoadResources();
    void Initiate();

    void AdaptPlayerPosition();
    void AdaptPlayerVelocity();

private:
    enum Layer
    {
        Background,
        Front,
        LayerCount
    };

public:
    

private:
    QueueInputCommands mCommandsQueue;

    sf::RenderWindow& mRender;
    sf::View mView;

    TexturesHolder mTextureHolder;
    SceneNode mSceneGraph;
    std::array<SceneNode*, Layer::LayerCount> mSceneLayers;

    Spaceship* mPlayerSpaceship;

    sf::FloatRect mWorldBounds;
    sf::Vector2f mSpawnPosition;
    float mScrolSpeed;
    sf::Vector2f mDeltaPlayerPosition;
};

