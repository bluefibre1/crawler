#pragma once

#include <string>
#include <map>

class Faction;
typedef std::shared_ptr<Faction> FactionSharedPtr;

class Faction
{
public:
    Faction(const std::string& name);

    void setFriendlyness(const FactionSharedPtr& faction, float value);

    bool isEnemy(const FactionSharedPtr& faction) const;

private:
    std::string m_name;
    typedef std::map<Faction*, float> Friendlynesses;
    Friendlynesses m_friendlynesses;
};

