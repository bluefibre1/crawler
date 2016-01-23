#include "chero.h"
#include "cinput.h"
#include "ccolors.h"
#include "cwindowmanager.h"

#include <stdlib.h>

Hero::Hero()
    : m_state(State::InGame)
    , m_statsPopup()
    , m_menuWindow()
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

    Input::setPause(m_state != State::InGame);

    switch (m_state)
    {
    case State::InGame:
        handleStateInGame(pressed, key);
        break;

    case State::Status:
        handleStateStatus(pressed, key);
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

    w->setTitle("Battle window");
    w->clear();

    w->print(Colors::ORANGE(), "NAME:");
    w->print(Colors::WHITE(), getName());

    w->print(Colors::ORANGE(), "\n");

    const int hpTotalBar = w->getWidth()-2;
    int hpBars = (int)((float)hpTotalBar * getHp() / getMaxHp());

    w->print(Colors::GREEN(), String(hpBars, '='));
    w->print(Colors::RED(), String(hpTotalBar-hpBars, 'x'));

    WindowManager::get().popup(w, 5);
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
        m_state = State::Status;
        break;

    case 'w':
    case 'W':
        hit(Direction::UP);
        break;
    }
}

void Hero::handleStateStatus(bool pressed, int key)
{
    showStatus();

    if (pressed)
    {
        switch (key)
        {
        case ' ':
            m_state = State::InGame;
            break;

        case 'i':
        case 'I':
            m_state = State::Inventory;
            break;
        }
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

        case 's':
        case 'S':
            m_state = State::Status;
            break;
        }
    }
}

void Hero::showStatus()
{
    if (!m_menuWindow)
    {
        m_menuWindow = WindowSharedPtr(new Window());
        m_menuWindow->setPosition(2, 1, 0);
        m_menuWindow->setHorizontalAlign(Window::HorizontalAlign::LEFT);
        m_menuWindow->setVerticalAlign(Window::VerticalAlign::BOTTOM);
        m_menuWindow->setMaxWidth(50);
    }

    Window* w = m_menuWindow.get();

    w->setTitle("Status");
    w->clear();

    w->print(Colors::ORANGE(), "NAME:");
    w->print(Colors::WHITE(), getName());

    w->print(Colors::ORANGE(), " HP:");
    w->print(Colors::WHITE(), std::to_string(getHp()));

    w->print(Colors::ORANGE(), " GOLD:");
    w->print(Colors::WHITE(), std::to_string(getGold()));

    w->print(Colors::ORANGE(), "\n");

    w->print(Colors::ORANGE(), "LEVEL:");
    w->print(Colors::WHITE(), std::to_string(getLevel()));

    w->print(Colors::ORANGE(), " XP:");
    w->print(Colors::WHITE(), std::to_string(getXp()));

    w->print(Colors::ORANGE(), " NEXT:");
    w->print(Colors::WHITE(), std::to_string(getNextLevelXp()));

    w->print(Colors::ORANGE(), "\n");
    w->print(Colors::ORANGE(), "\n");

    w->print(Colors::ORANGE(), "I: ");
    w->print(Colors::BLUE(), "inventory");

    WindowManager::get().popup(m_menuWindow, 0.1);
}

void Hero::showInventory()
{
    if (!m_menuWindow)
    {
        m_menuWindow = WindowSharedPtr(new Window());
        m_menuWindow->setPosition(2, 1, 0);
        m_menuWindow->setHorizontalAlign(Window::HorizontalAlign::LEFT);
        m_menuWindow->setVerticalAlign(Window::VerticalAlign::BOTTOM);
        m_menuWindow->setMaxWidth(50);
    }

    Window* w = m_menuWindow.get();

    w->setTitle("Inventory");
    w->clear();

    for (int i = 0; i < 10; ++i)
    {
        if (i >= (int)m_items.size())
        {
            break;
        }

        ItemPtr item = m_items[i];
        w->print(Colors::ORANGE(), std::to_string(i+1));
        w->print(Colors::ORANGE(), ": ");

        if (isEquipped(item))
        {
            w->print(Colors::YELLOW(), "<");
        }

        w->print(Colors::WHITE(), item->getName());

        if (isEquipped(item))
        {
            w->print(Colors::YELLOW(), ">");
        }

        w->print(Colors::ORANGE(), "\n");
    }

    w->print(Colors::ORANGE(), "\n");

    w->print(Colors::ORANGE(), "S: ");
    w->print(Colors::BLUE(), "status");

    WindowManager::get().popup(m_menuWindow, 0.1);
}
