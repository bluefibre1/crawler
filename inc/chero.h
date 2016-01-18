#pragma once

#include "ccharacter.h"
#include "cwindow.h"

class Hero : public Character
{
public:
    Hero();

    virtual void tick(float dt) override;

    virtual void draw(Renderer* r) override;

private:
    float m_refreshWindow;
    Window m_statisticWindow;
};

typedef std::shared_ptr<Hero> HeroSharedPtr;
