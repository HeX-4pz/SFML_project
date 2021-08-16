#pragma once
#include <array>

#include <SFML/Graphics.hpp>

#include "PlayerSpaceship.h"

class World : private sf::NonCopyable
{
public:
    World(sf::RenderWindow& window);
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

private:
    sf::RenderWindow& mRender;
    sf::View mView;

    TexturesHolder mTextureHolder;
    SceneNode mSceneGraph;
    std::array<SceneNode*, Layer::LayerCount> mSceneLayers;

    PlayerSpaceship* mPlayerSpaceship;

    sf::FloatRect mWorldBounds;
    sf::Vector2f mSpawnPosition;
    float mScrolSpeed;

};

