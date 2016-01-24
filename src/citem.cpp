#include "citem.h"


Item::Item()
    : m_owner(nullptr)
    , m_action(Action::NONE)
    , m_type(Type::NONE)
    , m_name()
{

}

void Item::setName(const String& name)
{
    m_name = name;
}

const std::string& Item::getName() const
{
    return m_name;
}

Item::Action Item::getAction() const
{
    return m_action;
}

Item::Type Item::getType() const
{
    return m_type;
}

Object* Item::getOwner() const
{
    return m_owner;
}

void Item::setOwner(Object* owner)
{
    m_owner = owner;
}
