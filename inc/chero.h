#pragma once

#include "ccharacter.h"
#include "cwindow.h"

class Hero : public Character
{
public:
    Hero();

    virtual void tick(float dt) override;

    virtual void draw(Camera* c, Renderer* r) override;

    virtual void showStats() override;

    void takeAll();

    virtual void onReceiveHit(Object* from, int damage) override;

    virtual void onGiveHit(Object* to, int damage) override;

    virtual int getObjectType() const override { return OBJECT_TYPE_CHARACTER|OBJECT_TYPE_HERO; }

private:
    enum class State
    {
        InGame,
            Status,
            Equip,
            Drop
    };

    State m_state;

    WindowWeakPtr m_hintPopup;
    WindowWeakPtr m_statsPopup;
    WindowSharedPtr m_menuWindow;
    int m_inventoryPage;

    void handleStateInGame(bool pressed, int key);
    void handleStateStatus(bool pressed, int key);
    void handleStateEquip(bool pressed, int key);
    void handleStateDrop(bool pressed, int key);

    void showHint();
    void showStatus();
    void showInventory();
};

typedef std::shared_ptr<Hero> HeroSharedPtr;
