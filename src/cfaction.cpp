#include "cfaction.h"


Faction::Faction(const std::string& name)
    : m_name(name)
    , m_friendlynesses()
{

}

void Faction::setFriendlyness(const FactionSharedPtr& faction, float value)
{
    m_friendlynesses.insert(Friendlynesses::value_type(faction.get(), value));
    faction->m_friendlynesses.insert(Friendlynesses::value_type(this, value));
}

bool Faction::isEnemy(const FactionSharedPtr& faction) const
{
    auto i = m_friendlynesses.find(faction.get());
    if (i != m_friendlynesses.end())
    {
        return (*i).second < 1;
    }
    return false;
}
