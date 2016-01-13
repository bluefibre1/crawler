#include "citem.h"


Item::Item()
    : m_name()
    , m_owner(nullptr)
    , m_isEquipable(false)
    , m_isUsable(false)
    , m_isWeapon(false)
    , m_isArmor(false)
{

}

void Item::setName(const std::string& name)
{
    m_name = name;
}

const std::string& Item::getName() const
{
    return m_name;
}

Object* Item::getOwner() const
{
    return m_owner;
}

void Item::setOwner(Object* owner)
{
    m_owner = owner;
}
