#include "ccharacter.h"
#include "crenderer.h"
#include "cbehavior.h"
#include "citem.h"
#include "ccolors.h"
#include "csimulator.h"
#include "cbehavior.h"
#include "cfactions.h"
#include "cmath.h"
#include "cinput.h"
#include "cwindowmanager.h"
#include "cdebugger.h"

Character::Character()
    : m_ch('@')
    , m_color(Colors::MAGENTA())
    , m_hp(100)
    , m_maxHp(150)
    , m_xp(0)
    , m_gold(10)
    , m_nextLevelXp(0)
    , m_level(1)
    , m_lastTickFrameId(-1)
    , m_behavior(nullptr)
    , m_blackboard(nullptr)
    , m_faction(nullptr)
    , m_name()
    , m_items()
    , m_equipped()
    , m_statsPopup()
{
    setNextLevelXp();
}

Character::~Character()
{
    setBehavior(nullptr);
    setBlackboard(nullptr);
}

void Character::draw(Renderer* r)
{
    if (r->isVisible(this))
    {
        if (m_hp)
        {
            r->draw(getX(), getY(), getZ(), m_color, Colors::INVALID(), m_ch);
            for (auto i = m_items.begin(); i != m_items.end(); i++)
            {
                const ItemSharedPtr& item = *i;
                item->draw(r);
            }
        }
        else
        {
            r->draw(getX(), getY(), getZ(), m_color, Colors::RED(), m_ch);
        }
        CDEBUG_MEDIUM(if (Debugger::get().getFrameId() == m_lastTickFrameId)
               {
                   debugStringAppend("t");
               }
               r->draw(getX(), getY()-1, Renderer::TOP(), Colors::YELLOW(), Colors::BLUE(), m_debugString);
            );
    }
}

void Character::tick(float dt)
{
    CDEBUG_LOW(m_debugString.clear());

    if (m_hp && !Input::isPaused())
    {
        if (m_behavior)
        {
            m_behavior->tick(dt, *m_blackboard);
        }
        Object::tick(dt);
        CDEBUG_MEDIUM(m_lastTickFrameId = Debugger::get().getFrameId());
    }
}

void Character::setBehavior(BehaviorNode* behavior)
{
    delete m_behavior;
    m_behavior = behavior;
}

void Character::setBlackboard(Blackboard* blackboard)
{
    delete m_blackboard;
    m_blackboard = blackboard;
}

void Character::setFaction(const FactionSharedPtr& faction)
{
    m_faction = faction;
}

const FactionSharedPtr& Character::getFaction() const
{
    return m_faction ? m_faction : Factions::DEFAULT();
}

const String& Character::getName() const
{
    return m_name;
}

void Character::setName(const String& name)
{
    m_name = name;
}

int Character::getHp() const
{
    return m_hp;
}

void Character::setMapHp(int hp)
{
    m_maxHp = hp;
}

int Character::getMaxHp() const
{
    return m_maxHp;
}

void Character::heal()
{
    m_hp = m_maxHp;
}

void Character::addXp(int xp)
{
    m_xp += xp;
    if (m_xp >= m_nextLevelXp)
    {
        m_level++;
        m_maxHp = (int)(m_maxHp * 1.1f);
        heal();
        setNextLevelXp();
    }
}

void Character::setNextLevelXp()
{
    m_nextLevelXp = m_level * m_level * 20;
}

int Character::getXp() const
{
    return m_xp;
}

int Character::getNextLevelXp() const
{
    return m_nextLevelXp;
}

int Character::getGold() const
{
    return m_gold;
}

int Character::getLevel() const
{
    return m_level;
}

void Character::setColor(const Color& color)
{
    m_color = color;
}

void Character::setChar(char ch)
{
    m_ch = ch;
}

void Character::addItem(const ItemSharedPtr& item)
{
    if (std::find(m_items.begin(), m_items.end(), item) == m_items.end())
    {
        m_items.push_back(item);
    }
    item->setOwner(this);
}

void Character::addItems(const ItemSharedPtrs& items)
{
    m_items.reserve(m_items.size() + items.size());
    m_items.insert(m_items.end(), items.begin(), items.end());
}

void Character::removeItem(const ItemSharedPtr& item)
{
    item->setOwner(nullptr);
    unequip(item);
    m_items.erase(std::remove(m_items.begin(), m_items.end(), item),
        m_items.end());
}

void Character::removeAllItems()
{
    m_items.clear();
}

const ItemSharedPtrs& Character::getItems() const
{
    return m_items;
}

void Character::equip(const ItemSharedPtr& item)
{
    addItem(item);
    if (item->getAction() == Item::Action::EQUIPPABLE)
    {
        auto i = std::find(m_equipped.begin(), m_equipped.end(), item);
        if (i == m_equipped.end())
        {
            m_equipped.erase(
                std::remove_if(
                    m_equipped.begin(), m_equipped.end(),
                    [item] (const ItemSharedPtr& equipped)
                    {
                        return equipped->getType() == item->getType();
                    }),
                m_equipped.end());

            m_equipped.push_back(item);
        }
    }
}

bool Character::isEquipped(const ItemSharedPtr& item)
{
    return std::find(m_equipped.begin(), m_equipped.end(), item) != m_equipped.end();
}

void Character::unequip(const ItemSharedPtr& item)
{
    m_equipped.erase(
        std::remove(m_equipped.begin(), m_equipped.end(), item),
        m_equipped.end());
}

void Character::hit(Direction dir)
{
    auto w = std::find_if(
        m_equipped.begin(), m_equipped.end(),
        [](const ItemSharedPtr& item)
        {
            return item->getType() == Item::Type::WEAPON;
        });

    if (w != m_equipped.end())
    {
        (*w)->use(dir);
    }
}

void Character::onReceiveHit(Object* from, int damage)
{
    int actualDmg = damage > m_hp ? m_hp : damage;
    m_hp -= actualDmg;
}

void Character::onGiveHit(Object* to, int damage)
{
    if (to->getObjectType() & OBJECT_TYPE_HERO)
    {
        showStats();
    }
}

void Character::showStats()
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

void Character::debugStringAppend(const String& value)
{
    if (!m_debugString.empty())
    {
        m_debugString += '|';
    }
    m_debugString += value;
}

bool Character::hasHint() const
{
    return !getHp() && !m_items.empty();
}

void Character::printHint(Window* w) const
{
    w->print(Colors::WHITE(), "Found ");
    w->print(Colors::RED(), "dead ");
    w->print(Colors::WHITE(), getName());
}
