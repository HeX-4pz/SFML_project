#include "World.h"
#include "SpriteNode.h"

World::World(sf::RenderWindow& window)
    : mRender(window)
    , mView(window.getDefaultView())
    , mTextureHolder()
    , mSceneGraph()
    , mPlayerSpaceship(nullptr)
    , mScrolSpeed(-50.f)
    , mWorldBounds(0.f, 0.f, mView.getSize().x, 2000.f)
    , mSpawnPosition(mView.getSize().x / 2.f, mWorldBounds.height - mView.getSize().y / 2.f)
{
    LoadResources();
    Initiate();
    mView.setCenter(mSpawnPosition);
}

void World::Update(sf::Time dTime)
{

    mView.move(0.f, mScrolSpeed * dTime.asSeconds());

    float leftLimit = mView.getCenter().x - mView.getSize().x / 2.f + 32.f;
    float topLimit = mView.getCenter().y - mView.getSize().y / 2.f + 32.f;
    float rightLimit = mView.getCenter().x + mView.getSize().x / 2.f - 32.f;
    float downLimit = mView.getCenter().y + mView.getSize().y / 2.f - 32.f;

    sf::Vector2f positionPlayer = mPlayerSpaceship->getPosition();

    if (positionPlayer.x < leftLimit)
        positionPlayer.x = leftLimit;

    if (positionPlayer.x > rightLimit)
        positionPlayer.x = rightLimit;

    if (positionPlayer.y < topLimit)
        positionPlayer.y = topLimit;

    if (positionPlayer.y > downLimit)
        positionPlayer.y = downLimit;

    if (mPlayerSpaceship->getPosition() != positionPlayer)
    {
        mPlayerSpaceship->setPosition(positionPlayer);
    }

    mSceneGraph.Update(dTime);
}

void World::Draw()
{
    mRender.setView(mView);
    mRender.draw(mSceneGraph);
}

void World::HadlePlayerInput(sf::Keyboard::Key key, bool pressed)
{
    sf::Vector2f speed;
    if (!pressed)
    {
        speed.x = 0;
        speed.y = mScrolSpeed;
    }
    else if (key == sf::Keyboard::W)
    {
        speed.x = 0;
        speed.y = mScrolSpeed - mPlayerSpaceship->GetSpeedLimits().y;
    }
    else if (key == sf::Keyboard::S)
    {
        speed.x = 0;
        speed.y = mScrolSpeed + mPlayerSpaceship->GetSpeedLimits().y;
    }
    else if (key == sf::Keyboard::A)
    {
        speed.x = -mPlayerSpaceship->GetSpeedLimits().x;
        speed.y = mScrolSpeed;
    }
    else if (key == sf::Keyboard::D)
    {
        speed.x = mPlayerSpaceship->GetSpeedLimits().x;
        speed.y = mScrolSpeed;
    }

    mPlayerSpaceship->SetVelocity(speed);
}

void World::LoadResources()
{
    mTextureHolder.Load(Textures::Spaceship_Eagle, "resources/tex/Spaceship.png");
    mTextureHolder.Load(Textures::Spaceship_Raptor, "resources/tex/Raptor.png");
    mTextureHolder.Load(Textures::Desert, "resources/tex/Desert.png");
}

void World::Initiate()
{
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        SceneNode::uPtr layer(new SceneNode());
        mSceneLayers[i] = layer.get();

        mSceneGraph.AttachChild(std::move(layer));
    }

    sf::Texture& texture = mTextureHolder.Get(Textures::Desert);
    sf::IntRect rect(mWorldBounds);
    texture.setRepeated(true);

    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, rect));
    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayers[Background]->AttachChild(std::move(backgroundSprite));

    std::unique_ptr<Spaceship> player(new Spaceship(Spaceship::Eagle, mTextureHolder));
    mPlayerSpaceship = player.get();
    mPlayerSpaceship->setPosition(mSpawnPosition);
    mPlayerSpaceship->SetVelocity(0, mScrolSpeed);
    mPlayerSpaceship->SetSpeedLimits(sf::Vector2f(500.f, 500.f));
    mSceneLayers[Front]->AttachChild(std::move(player));

    std::unique_ptr<Spaceship> leftEscort(new Spaceship(Spaceship::Raptor, mTextureHolder));
    leftEscort->setPosition(-80.f, 50.f);
    mPlayerSpaceship->AttachChild(std::move(leftEscort));

    std::unique_ptr<Spaceship> rightEscort(new Spaceship(Spaceship::Raptor, mTextureHolder));
    rightEscort->setPosition(80.f, 50.f);
    mPlayerSpaceship->AttachChild(std::move(rightEscort));

}
