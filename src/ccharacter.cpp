#include "ccharacter.h"
#include "crenderer.h"
#include "cbehavior.h"
#include "citem.h"
#include "ccolors.h"
#include "csimulator.h"
#include "cbehavior.h"
#include "cfactions.h"
#include "cmath.h"

Character::Character()
    : m_ch('@')
    , m_color(Colors::MAGENTA())
    , m_hp(10)
    , m_maxHp(10)
    , m_xp(0)
    , m_gold(0)
    , m_nextLevelXp(0)
    , m_level(1)
    , m_behavior(nullptr)
    , m_name()
    , m_items()
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
                const ItemPtr& item = *i;
                item->draw(r);
            }
        }
        else
        {
            r->draw(getX(), getY(), getZ(), m_color, Colors::RED(), m_ch);
        }
    }
}

void Character::tick(float dt)
{
    if (m_behavior && m_hp)
    {
        m_behavior->tick(dt, *m_blackboard);
    }
    Object::tick(dt);
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

void Character::setFaction(Faction* faction)
{
    m_faction = faction;
}

Faction* Character::getFaction() const
{
    return m_faction ? m_faction : &Factions::DEFAULT();
}

const std::string& Character::getName() const
{
    return m_name;
}

void Character::setName(const std::string& name)
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

void Character::addItem(const ItemPtr& item)
{
    auto i = std::find(m_items.begin(), m_items.end(), item);
    if (i == m_items.end())
    {
        m_items.push_back(item);
    }
    item->setOwner(this);
}

void Character::removeItem(const ItemPtr& item)
{
    item->setOwner(nullptr);
    unequip(item);
    auto i = std::find(m_items.begin(), m_items.end(), item);
    if (i != m_items.end())
    {
        m_items.erase(i);
    }
}

void Character::equip(const ItemPtr& item)
{
    addItem(item);
    if (item->isEquipable())
    {
        auto i = std::find(m_equipped.begin(), m_equipped.end(), item);
        if (i == m_equipped.end())
        {
            m_equipped.push_back(item);
        }
    }
}

void Character::unequip(const ItemPtr& item)
{
    auto i = std::find(m_equipped.begin(), m_equipped.end(), item);
    if (i == m_equipped.end())
    {
        m_equipped.push_back(item);
    }
}

void Character::hit(Direction dir)
{
    Item* weapon = nullptr;
    for (auto i = m_items.begin(); i != m_items.end(); ++i)
    {
        if ((*i)->isWeapon())
        {
            weapon = (*i).get();
        }
    }

    if (weapon)
    {
        weapon->use(dir);
    }
}

void Character::onReceiveHit(Object* /*from*/, int damage)
{
    showStats();
    int actualDmg = damage > m_hp ? m_hp : damage;
    m_hp -= actualDmg;
}

void Character::onGiveHit(Object* to, int damage)
{
    showStats();
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
