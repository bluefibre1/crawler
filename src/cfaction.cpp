#include "cfaction.h"


Faction::Faction(const std::string& name)
    : m_name(name)
    , m_friendlynesses()
{

}

void Faction::setFriendlyness(Faction* faction, float value)
{
    m_friendlynesses.insert(Friendlynesses::value_type(faction, value));
    faction->m_friendlynesses.insert(Friendlynesses::value_type(this, value));
}

bool Faction::isEnemy(Faction* faction) const
{
    auto i = m_friendlynesses.find(faction);
    if (i != m_friendlynesses.end())
    {
        return (*i).second < 1;
    }
    return false;
}
