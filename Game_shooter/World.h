#pragma once
#include <array>

#include <SFML/Graphics.hpp>

#include "Spaceship.h"

class World : private sf::NonCopyable
{
public:
    World(sf::RenderWindow& window);
    void Update(sf::Time dTime);
    void Draw();

    void HadlePlayerInput(sf::Keyboard::Key key, bool pressed);

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

    Spaceship* mPlayerSpaceship;

    sf::FloatRect mWorldBounds;
    sf::Vector2f mSpawnPosition;
    float mScrolSpeed;

};

