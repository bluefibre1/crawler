#include "chero.h"
#include "cinput.h"
#include "ccolors.h"
#include "cwindowmanager.h"

#include <stdlib.h>

Hero::Hero()
{
    m_color = Colors::MAGENTA();
    m_ch = '0';
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
        // only when alive
        if (getHp())
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
            }
        }

        // always
        switch (key)
        {
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
    Character::draw(r);
}

void Hero::showStats()
{
    WindowSharedPtr w(m_statsPopup.expired() ?
                      WindowSharedPtr(new Window()) : m_statsPopup.lock());
    m_statsPopup = w;

    w->setHorizontalAlign(Window::HorizontalAlign::LEFT);
    w->setVerticalAlign(Window::VerticalAlign::TOP);

    w->clear();

    w->print(Colors::ORANGE(), "NAME:");
    w->print(Colors::WHITE(), getName());

    w->print(Colors::ORANGE(), "\n");

    w->print(Colors::ORANGE(), "HP:");
    w->print(Colors::WHITE(), std::to_string(getHp()));

    w->print(Colors::ORANGE(), "\n");

    w->print(Colors::ORANGE(), "LEVEL:");
    w->print(Colors::WHITE(), std::to_string(getLevel()));

    WindowManager::get().popup(w, 10);
}
