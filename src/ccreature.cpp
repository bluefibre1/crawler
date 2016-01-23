#include "ccreature.h"
#include "cwindowmanager.h"
#include "ccolors.h"
#include "cinput.h"

Creature::Creature()
    : m_maxVelocity(1)
    , m_statsPopup()
{
}

void Creature::tick(float dt)
{
    if (!Input::isPaused())
    {
        Character::tick(dt);
    }
}

void Creature::setMaxVelocity(float maxVel)
{
    m_maxVelocity = maxVel;
}

void Creature::showStats()
{
    WindowSharedPtr w(m_statsPopup.expired() ?
                      WindowSharedPtr(new Window()) : m_statsPopup.lock());
    m_statsPopup = w;

    w->setHorizontalAlign(Window::HorizontalAlign::RIGHT);
    w->setVerticalAlign(Window::VerticalAlign::TOP);

    w->clear();

    w->print(Colors::ORANGE(), "NAME:");
    w->print(Colors::WHITE(), getName());

    w->print(Colors::ORANGE(), "\n");

    const int hpTotalBar = w->getWidth()-2;
    int hpBars = (int)((float)hpTotalBar * getHp() / getMaxHp());

    w->print(Colors::GREEN(), String(hpBars, '='));
    w->print(Colors::RED(), String(hpTotalBar-hpBars, 'x'));

    WindowManager::get().popup(w, 3);
}
