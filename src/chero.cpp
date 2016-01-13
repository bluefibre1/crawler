#include "chero.h"
#include "cinput.h"
#include "ccolors.h"

#include <stdlib.h>

const float HERO_VELOCITY = 1;

Hero::Hero()
{
    m_color = Colors::MAGENTA();
    m_ch = '0';

    m_statisticWindow.setPosition(2, 2, 0);
    m_statisticWindow.setBorderWidth(1, 1);
    m_statisticWindow.print(Colors::ORANGE(), "HP:");
    m_statisticWindow.print(Colors::WHITE(), std::to_string(m_hp));

    //m_statisticWindow.print(Colors::ORANGE(), "LEVEL:");
    //m_statisticWindow.print(Colors::WHITE(), std::to_string(m_level));

}

void Hero::tick(float dt)
{
    bool pressed(false);
    int key;
    while (Input::getKey(key))
    {
        pressed = true;
    }

    if (pressed)
    {
        switch (key)
        {
        case (int)Key::UP:
            setVelocity(0, -HERO_VELOCITY/dt, 0);
            break;

        case (int)Key::DOWN:
            setVelocity(0, HERO_VELOCITY/dt, 0);
            break;

        case (int)Key::LEFT:
            setVelocity(-HERO_VELOCITY/dt, 0, 0);
            break;

        case (int)Key::RIGHT:
            setVelocity(HERO_VELOCITY/dt, 0, 0);
            break;

        case 'q':
        case 'Q':
            Input::setQuit();
            break;
        }
    }

    Character::tick(dt);
}

void Hero::draw(Renderer* r)
{
    m_statisticWindow.draw(r);
    Character::draw(r);
}
