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
    ~World();

    void Update(sf::Time dTime);
    void Draw();

    sf::FloatRect GetCurrentBouds();
    float GetScrollSpeed();

private:
    void LoadResources();
    void Initiate();

private:
    enum Layer
    {
        Background,
        Front,
        LayerCount
    };

public:
    QueueInputCommands* mCommandsQueue;

private:
    sf::RenderWindow& mRender;
    sf::View mView;

    TexturesHolder mTextureHolder;
    SceneNode mSceneGraph;
    std::array<SceneNode*, Layer::LayerCount> mSceneLayers;

    Spaceship* mPlayerSpaceship;

    sf::FloatRect mWorldBounds;
    sf::Vector2f mSpawnPosition;
    float mScrolSpeed;

};

