#pragma once

#include <string>
#include <map>

class Faction
{
public:
    Faction(const std::string& name);

    void setFriendlyness(Faction* faction, float value);

    bool isEnemy(Faction* faction) const;

private:
    std::string m_name;
    typedef std::map<Faction*, float> Friendlynesses;
    Friendlynesses m_friendlynesses;
};
