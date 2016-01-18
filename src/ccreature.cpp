#include "ccreature.h"
#include "cwindowmanager.h"
#include "ccolors.h"

Creature::Creature()
    : m_maxVelocity(1)
    , m_statsPopup()
{
}

void Creature::tick(float dt)
{
    Character::tick(dt);
}

void Creature::setMaxVelocity(float maxVel)
{
    m_maxVelocity = maxVel;
}

void Creature::showStats()
{
    WindowSharedPtr w(m_statsPopup.expired() ?
                      WindowSharedPtr(new Window()) : m_statsPopup.lock());

    w->setHorizontalAlign(Window::HorizontalAlign::RIGHT);
    w->setPosition(2, 1, 0);
    w->clear();

    w->print(Colors::ORANGE(), "NAME:");
    w->print(Colors::WHITE(), getName());

    w->print(Colors::ORANGE(), "\n");

    w->print(Colors::ORANGE(), "HP:");
    w->print(Colors::WHITE(), std::to_string(getHp()));

    w->print(Colors::ORANGE(), "\n");

    w->print(Colors::ORANGE(), "LEVEL:");
    w->print(Colors::WHITE(), std::to_string(getLevel()));

    WindowManager::get().popup(w, 3);
}
