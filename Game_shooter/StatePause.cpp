#include "StatePause.h"
#include "Button.h"

StatePause::StatePause(StateStack& stack, Context context) 
    : State(stack, context)
    , mGUIContainer()
    , mShape()
{
    sf::Vector2f viewSize = context.mWindow->getView().getSize();
    sf::Vector2f viewPos = context.mWindow->getView().getCenter() - viewSize / 2.f;

    mShape.setSize(viewSize);
    mShape.setFillColor(sf::Color(0, 0, 0, 150));

    float y = viewPos.y + viewSize.y * 1.f / 3.f;

    sf::Vector2f startPoint = sf::Vector2f(context.mWindow->getView().getCenter().x, y);
    
    GUI::Button::Ptr bt_resume = std::make_shared<GUI::Button>(*context.mFonts, *context.mTextures);
    GUI::Button::Ptr bt_menu = std::make_shared<GUI::Button>(*context.mFonts, *context.mTextures);

    bt_resume->SetText("Resume");
    bt_menu->SetText("Menu");

    bt_resume->setScale(0.8f, 0.7f);
    bt_menu->setScale(0.8f, 0.7f);
    
    bt_resume->setPosition(viewPos.x + viewSize.x * 0.5f - bt_resume->GetLocalBounds().width / 2.f, y);
    bt_menu->setPosition(viewPos.x + viewSize.x * 0.5f - bt_menu->GetLocalBounds().width / 2.f, y + 60.f);

    bt_resume->SetCallback([this]() 
    {
        requestPopState();
    });

    bt_menu->SetCallback([this]()
    {
        requestClearStates();
        requestPushState(States::MainMenu);
    });

    mGUIContainer.Pack(bt_resume);
    mGUIContainer.Pack(bt_menu);


}

void StatePause::Draw()
{
    sf::RenderWindow* render = GetContext()->mWindow;
    render->setView(render->getDefaultView());
    
    render->draw(mShape);
    render->draw(mGUIContainer);
}

bool StatePause::Update(sf::Time dTime)
{
    return false;
}

bool StatePause::HandleInput(const sf::Event& event)
{   
    mGUIContainer.HandleEvent(event);

    return false;
}
