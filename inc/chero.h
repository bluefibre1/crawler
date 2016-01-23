#pragma once

#include "ccharacter.h"
#include "cwindow.h"

class Hero : public Character
{
public:
    Hero();

    virtual void tick(float dt) override;

    virtual void draw(Renderer* r) override;

    virtual void showStats() override;

private:
    enum class State
    {
        InGame,
            Status,
            Inventory
    };

    State m_state;

    WindowWeakPtr m_statsPopup;
    WindowSharedPtr m_menuWindow;

    void handleStateInGame(bool pressed, int key);
    void handleStateStatus(bool pressed, int key);
    void handleStateInventory(bool pressed, int key);

    void showStatus();
    void showInventory();
};

typedef std::shared_ptr<Hero> HeroSharedPtr;
