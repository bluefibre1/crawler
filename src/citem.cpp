#include "citem.h"


Item::Item()
    : m_name()
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
