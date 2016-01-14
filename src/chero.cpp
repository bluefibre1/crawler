#include "chero.h"
#include "cinput.h"
#include "ccolors.h"

#include <stdlib.h>

Hero::Hero()
{
    m_color = Colors::MAGENTA();
    m_ch = '0';

    m_statisticWindow.setPosition(2, 2, 0);
    m_statisticWindow.setBorderWidth(1, 1);
    m_statisticWindow.print(Colors::WHITE(), "HP:");
    m_statisticWindow.print(Colors::WHITE(), std::to_string(getHp()));
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
            setDisplacement(0, -1);
            break;

        case (int)Key::DOWN:
            setDisplacement(0, 1);
            break;

        case (int)Key::LEFT:
            setDisplacement(-1, 0);
            break;

        case (int)Key::RIGHT:
            setDisplacement(1, 0);
            break;

        case 'a':
        case 'A':
            hit(Direction::LEFT);
            break;

        case 'd':
        case 'D':
            hit(Direction::RIGHT);
            break;

        case 's':
        case 'S':
            hit(Direction::DOWN);
            break;

        case 'w':
        case 'W':
            hit(Direction::UP);
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
