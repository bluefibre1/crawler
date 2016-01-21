#include "chero.h"
#include "cinput.h"
#include "ccolors.h"
#include "cwindowmanager.h"

#include <stdlib.h>

Hero::Hero()
    : m_state(State::InGame)
    , m_statsPopup()
    , m_inventoryWindow()
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

    switch (m_state)
    {
    case State::InGame:
        handleStateInGame(pressed, key);
        break;

    case State::Inventory:
        handleStateInventory(pressed, key);
        break;
    }

    if (pressed)
    {
        // always
        switch (key)
        {
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

    w->print(Colors::ORANGE(), "\n");

    w->print(Colors::ORANGE(), "XP:");
    w->print(Colors::WHITE(), std::to_string(getXp()));

    WindowManager::get().popup(w, 10);
}

void Hero::handleStateInGame(bool pressed, int key)
{
    // only when alive
    if (!getHp() || !pressed)
    {
        return;
    }

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

    case ' ':
        m_state = State::Inventory;
        break;

    case 'w':
    case 'W':
        hit(Direction::UP);
        break;
    }
}

void Hero::handleStateInventory(bool pressed, int key)
{
    showInventory();

    if (pressed)
    {
        switch (key)
        {
        case ' ':
            m_state = State::InGame;
            break;
        }
    }
}

void Hero::showInventory()
{
    if (!m_inventoryWindow)
    {
        m_inventoryWindow = WindowSharedPtr(new Window());
        m_inventoryWindow->setPosition(2, 1, 0);
        m_inventoryWindow->setHorizontalAlign(Window::HorizontalAlign::LEFT);
        m_inventoryWindow->setVerticalAlign(Window::VerticalAlign::BOTTOM);
        m_inventoryWindow->setTitle("Inventory");
        m_inventoryWindow->setMaxWidth(50);
    }

    Window* w = m_inventoryWindow.get();

    w->clear();

    w->print(Colors::ORANGE(), "NAME:");
    w->print(Colors::WHITE(), getName());

    w->print(Colors::ORANGE(), "    HP:");
    w->print(Colors::WHITE(), std::to_string(getHp()));

    w->print(Colors::ORANGE(), "    GOLD:");
    w->print(Colors::WHITE(), std::to_string(getGold()));

    w->print(Colors::ORANGE(), "\n");

    w->print(Colors::ORANGE(), "LEVEL:");
    w->print(Colors::WHITE(), std::to_string(getLevel()));

    w->print(Colors::ORANGE(), "    XP:");
    w->print(Colors::WHITE(), std::to_string(getXp()));

    w->print(Colors::ORANGE(), "    NEXT:");
    w->print(Colors::WHITE(), std::to_string(getNextLevelXp()));

    WindowManager::get().popup(m_inventoryWindow, 0.1);
}
