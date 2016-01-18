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
    float m_refreshWindow;
    WindowSharedPtr m_statisticWindow;
};

typedef std::shared_ptr<Hero> HeroSharedPtr;
