#include "chero.h"
#include "cinput.h"
#include "ccolors.h"
#include "cwindowmanager.h"
#include "cmath.h"
#include "csimulator.h"

static const int INVENTORY_PAGE_SIZE = 5;


Hero::Hero()
    : m_state(State::InGame)
    , m_statsPopup()
    , m_menuWindow()
    , m_inventoryPage(0)
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

    case State::Status:
        handleStateStatus(pressed, key);
        break;

    case State::Equip:
        handleStateEquip(pressed, key);
        break;

    case State::Drop:
        handleStateDrop(pressed, key);
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

void Hero::takeAll()
{
    Object* dest = nullptr;
    if (Simulator::get().findObjectAt(
            getX(),
            getY(),
            getZ(),
            &dest))
    {
        if (dest->isCharacter())
        {
            Character* target = (Character*)dest;
            if (target->getHp() == 0)
            {
                addItems(target->getItems());
                target->removeAllItems();
            }
        }
    }
}

void Hero::onGiveHit(Object* to, int damage)
{
    Character::onGiveHit(to, damage);
    if (to->isCharacter() && damage)
    {
        Character* target = (Character*)to;

        int levelDiff = target->getLevel() - getLevel();
        float factor = levelDiff >= 0 ? levelDiff+1 : -1.0f/levelDiff;
        int dxp = damage * factor;

        addXp(dxp);

        if (target->getHp() <= 0)
        {
            addXp(target->getLevel() * 10 * factor);
        }
    }
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

    case 't':
    case 'T':
        takeAll();
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

    case ' ':
        m_state = State::Status;
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

        case 'e':
        case 'E':
            m_state = State::Equip;
            break;

        case 'd':
        case 'D':
            m_state = State::Drop;
            break;
        }
    }
}

void Hero::handleStateEquip(bool pressed, int key)
{
    showInventory();

    if (pressed)
    {
        switch (key)
        {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        {
            int i = m_inventoryPage * INVENTORY_PAGE_SIZE + key - '1';
            if (i < (int)m_items.size())
            {
                ItemSharedPtr item = m_items[i];
                if (isEquipped(item))
                {
                    unequip(item);
                }
                else
                {
                    equip(item);
                }
            }
        }
        break;

        case 'n':
        case 'N':
        {
            m_inventoryPage++;
            if (m_inventoryPage * INVENTORY_PAGE_SIZE > (int)m_items.size())
            {
                m_inventoryPage = 0;
            }
        }
        break;

        case ' ':
            m_state = State::InGame;
            break;

        case 's':
        case 'S':
            m_state = State::Status;
            break;

        case 'd':
        case 'D':
            m_state = State::Drop;
            break;
        }
    }
}

void Hero::handleStateDrop(bool pressed, int key)
{
    showInventory();

    if (pressed)
    {
        switch (key)
        {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        {
            int i = m_inventoryPage * INVENTORY_PAGE_SIZE + key - '1';
            if (i < (int)m_items.size())
            {
                ItemSharedPtr item = m_items[i];
                removeItem(item);
            }
        }
        break;

        case 'n':
        case 'N':
        {
            m_inventoryPage++;
            if (m_inventoryPage * INVENTORY_PAGE_SIZE > (int)m_items.size())
            {
                m_inventoryPage = 0;
            }
        }
        break;

        case ' ':
            m_state = State::InGame;
            break;

        case 'e':
        case 'E':
            m_state = State::Equip;
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

    w->print(Colors::ORANGE(), "e: ");
    w->print(Colors::ORANGE(), "equip");

    w->print(Colors::ORANGE(), " d: ");
    w->print(Colors::ORANGE(), "drop");

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

    if (m_state == State::Drop)
    {
        w->setTitle("Inventory Drop");
    }
    else
    {
        w->setTitle("Inventory Equip");
    }
    w->clear();

    Math::clamp(m_inventoryPage, 0, (m_items.size() - 1) / INVENTORY_PAGE_SIZE);

    for (int i = 0; i < INVENTORY_PAGE_SIZE; ++i)
    {
        int idx = i + m_inventoryPage * INVENTORY_PAGE_SIZE;
        if (idx >= (int)m_items.size())
        {
            break;
        }

        ItemSharedPtr item = m_items[idx];
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
    w->print(Colors::ORANGE(), "status");

    if (m_state == State::Equip)
    {
        w->print(Colors::ORANGE(), " D: ");
        w->print(Colors::ORANGE(), "drop");
    }
    else
    {
        w->print(Colors::ORANGE(), " E: ");
        w->print(Colors::ORANGE(), "equip");
    }

    w->print(Colors::ORANGE(), " N: ");
    w->print(Colors::ORANGE(), "next");

    WindowManager::get().popup(m_menuWindow, 0.1);
}
