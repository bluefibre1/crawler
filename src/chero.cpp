#include "chero.h"
#include "cinput.h"

#include <stdlib.h>

const float HERO_VELOCITY = 1;

Hero::Hero()
{
    m_tile = Tile(ColorStyle::BRIGHT, Color::MAGENTA, Color::INVALID, '0');

    m_statisticWindow.setPosition(2, 2, 0);
    m_statisticWindow.setBorderWidth(1, 1);
    m_statisticWindow.print(Color::WHITE, ColorStyle::BRIGHT, "HP:");
    m_statisticWindow.print(Color::WHITE, ColorStyle::NORMAL, std::to_string(m_hp));
}

void Hero::tick(float dt)
{
    int key;
    if (Input::getKey(key))
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
