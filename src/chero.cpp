#include "chero.h"
#include "cinput.h"
#include "ccolors.h"
#include "cwindowmanager.h"
#include "cmath.h"
#include "csimulator.h"
#include "cweapon.h"
#include "cchest.h"
#include "cdebugger.h"

static const int INVENTORY_PAGE_SIZE = 5;


Hero::Hero()
    : m_state(State::InGame)
    , m_hintPopup()
    , m_statsPopup()
    , m_menuWindow()
    , m_inventoryPage(0)
{
    m_color = Colors::MAGENTA();
    m_ch = CHAR_T('&');
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

        case 'R':
            heal();
            break;

        case '`':
            Debugger::get().cycleDebugLevel();
        }
    }

    showHint();

    Character::tick(dt);
}

void Hero::draw(Camera* c, Renderer* r)
{
    Character::draw(c, r);
}

void Hero::showHint()
{
    ObjectWeakPtrs objs;
    Simulator::get().findObjectsAround(getX(), getY(), getZ(), 5, &objs);

    ObjectSharedPtr objectWithHint;
    for (auto i = objs.begin(); i != objs.end(); ++i)
    {
        ObjectSharedPtr obj = (*i).lock();
        if (obj && obj->hasHint())
        {
            objectWithHint = obj;
            break;
        }
    }

    if (!objectWithHint)
    {
        return;
    }

    WindowSharedPtr w(m_hintPopup.expired() ?
                      WindowSharedPtr(new Window()) : m_hintPopup.lock());
    m_hintPopup = w;

    w->setHorizontalAlign(Window::HorizontalAlign::CENTER);
    w->setVerticalAlign(Window::VerticalAlign::BOTTOM);
    //w->setBorderWidth(1, 0);
    w->clear();

    objectWithHint->printHint(w.get());

    WindowManager::get().popup(w, 5);
}

void Hero::showStats()
{
    WindowSharedPtr w(m_statsPopup.expired() ?
                      WindowSharedPtr(new Window()) : m_statsPopup.lock());
    m_statsPopup = w;

    w->setHorizontalAlign(Window::HorizontalAlign::LEFT);
    w->setVerticalAlign(Window::VerticalAlign::TOP);

    w->setTitle(CHAR_T("Battle window"));
    w->clear();

    w->print(Colors::ORANGE(), CHAR_T("NAME:"));
    w->print(Colors::WHITE(), getName());

    w->print(Colors::ORANGE(), CHAR_T("\n"));

    const int hpTotalBar = w->getWidth()-2;
    int hpBars = (int)((float)hpTotalBar * getHp() / getMaxHp());

    w->print(Colors::GREEN(), String(hpBars, CHAR_T('=')));
    w->print(Colors::RED(), String(hpTotalBar-hpBars, CHAR_T('-')));

    WindowManager::get().popup(w, 5);
}

void Hero::takeAll()
{
    ObjectWeakPtrs objects;
    if (Simulator::get().listObjectsAt(
            getX(),
            getY(),
            getZ(),
            &objects))
    {
        ItemSharedPtrs items;
        std::for_each(
            objects.begin(), objects.end(), [&items](const ObjectWeakPtr& o)
            {
                ObjectSharedPtr object = o.lock();
                if (object->getObjectType() & OBJECT_TYPE_CHARACTER)
                {
                    Character* target = (Character*)object.get();
                    if (target->getHp() == 0)
                    {
                        items.reserve(items.size() + target->getItems().size());
                        items.insert(items.end(), target->getItems().begin(), target->getItems().end());
                        target->removeAllItems();
                    }
                }
                else if (object->getObjectType() & OBJECT_TYPE_CHEST)
                {
                    Chest* target = (Chest*)object.get();
                    items.reserve(items.size() + target->getItems().size());
                    items.insert(items.end(), target->getItems().begin(), target->getItems().end());
                    target->removeAllItems();
                }
            });

        if (!items.empty())
        {
            WindowSharedPtr w(new Window());
            w->setHorizontalAlign(Window::HorizontalAlign::CENTER);
            w->setVerticalAlign(Window::VerticalAlign::BOTTOM);
            w->setTitle(CHAR_T("Added To Inventory"));
            w->setMaxWidth(50);

            bool first = true;
            for_each(items.begin(), items.end(),
                     [w, &first] (const ItemSharedPtr& item)
                     {
                         if (!first)
                         {
                             w->printEndLine();
                         }
                         first = false;
                         w->print(Colors::WHITE(), item->getName());
                     });

            WindowManager::get().popup(w, 5);

            addItems(items);
        }
    }
}

void Hero::onReceiveHit(Object* from, int damage)
{
    Character::onReceiveHit(from, damage);
    showStats();
    if (from->getObjectType() & OBJECT_TYPE_CHARACTER)
    {
        Character* attacker = (Character*)from;
        attacker->showStats();
    }
}

void Hero::onGiveHit(Object* to, int damage)
{
    Character::onGiveHit(to, damage);
    showStats();
    if (to->getObjectType() & OBJECT_TYPE_CHARACTER)
    {
        Character* target = (Character*)to;
        target->showStats();
        if (damage)
        {
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

    w->setTitle(CHAR_T("Status"));
    w->clear();

    w->print(Colors::ORANGE(), CHAR_T("NAME:"));
    w->print(Colors::WHITE(), getName());

    w->print(Colors::ORANGE(), CHAR_T(" HP:"));
    w->print(Colors::WHITE(), std::to_wstring(getHp()));

    w->print(Colors::ORANGE(), CHAR_T(" GOLD:"));
    w->print(Colors::WHITE(), std::to_wstring(getGold()));

    w->print(Colors::ORANGE(), CHAR_T("\n"));

    w->print(Colors::ORANGE(), CHAR_T("LEVEL:"));
    w->print(Colors::WHITE(), std::to_wstring(getLevel()));

    w->print(Colors::ORANGE(), CHAR_T(" XP:"));
    w->print(Colors::WHITE(), std::to_wstring(getXp()));

    w->print(Colors::ORANGE(), CHAR_T(" NEXT:"));
    w->print(Colors::WHITE(), std::to_wstring(getNextLevelXp()));

    w->print(Colors::ORANGE(), CHAR_T("\n"));
    w->print(Colors::ORANGE(), CHAR_T("\n"));

    w->print(Colors::ORANGE(), CHAR_T("e: "));
    w->print(Colors::ORANGE(), CHAR_T("equip"));

    w->print(Colors::ORANGE(), CHAR_T(" d: "));
    w->print(Colors::ORANGE(), CHAR_T("drop"));

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
        w->setTitle(CHAR_T("Inventory Drop"));
    }
    else
    {
        w->setTitle(CHAR_T("Inventory Equip"));
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
        w->print(Colors::ORANGE(), std::to_wstring(i+1));
        w->print(Colors::ORANGE(), CHAR_T(": "));

        if (isEquipped(item))
        {
            w->print(Colors::YELLOW(), CHAR_T("<"));
        }

        w->print(Colors::WHITE(), item->getName());

        if (isEquipped(item))
        {
            w->print(Colors::YELLOW(), CHAR_T(">"));
        }

        if (item->getType() == Item::Type::WEAPON)
        {
            w->print(Colors::ORANGE(), CHAR_T(" D:"));
            w->print(Colors::RED(), std::to_wstring(((Weapon*)item.get())->getDamage()));
        }

        w->printEndLine();
    }

    w->printEndLine();

    w->print(Colors::ORANGE(), CHAR_T("S: "));
    w->print(Colors::ORANGE(), CHAR_T("status"));

    if (m_state == State::Equip)
    {
        w->print(Colors::ORANGE(), CHAR_T(" D: "));
        w->print(Colors::ORANGE(), CHAR_T("drop"));
    }
    else
    {
        w->print(Colors::ORANGE(), CHAR_T(" E: "));
        w->print(Colors::ORANGE(), CHAR_T("equip"));
    }

    w->print(Colors::ORANGE(), CHAR_T(" N: "));
    w->print(Colors::ORANGE(), CHAR_T("next"));

    WindowManager::get().popup(m_menuWindow, 0.1);
}
