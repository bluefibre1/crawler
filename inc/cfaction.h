#pragma once


class Faction
{
public:
    Faction(const std::string& name);

    void setFriendlyness(Faction* faction, float value);

    bool isEnemy(const Faction* faction) const;

private:

};
