#pragma once

#include "cobject.h"
#include "ccolor.h"
#include "citem.h"
#include "cdirection.h"

#include <string>
#include <vector>

class BehaviorNode;
class Blackboard;
class Faction;

typedef std::vector<ItemSharedPtr> ItemSharedPtrs;

class Character : public Object
{
public:
    Character();
    ~Character();

    virtual void draw(Renderer* r) override;

    virtual void tick(float dt) override;

    void setBehavior(BehaviorNode* behavior);

    void setBlackboard(Blackboard* blackboard);

    void setFaction(Faction* faction);

    Faction* getFaction() const;

    const std::string& getName() const;

    void setName(const std::string& name);

    int getHp() const;

    void setMapHp(int hp);

    int getMaxHp() const;

    void heal();

    void addXp(int xp);

    int getXp() const;

    int getNextLevelXp() const;

    int getGold() const;

    int getLevel() const;

    void setColor(const Color& color);

    void setChar(char ch);

    void addItem(const ItemSharedPtr& item);

    void addItems(const ItemSharedPtrs& items);

    void removeItem(const ItemSharedPtr& item);

    void removeAllItems();

    const ItemSharedPtrs& getItems() const;

    void equip(const ItemSharedPtr& item);

    void unequip(const ItemSharedPtr& item);

    bool isEquipped(const ItemSharedPtr& item);

    void hit(Direction dir);

    virtual void onReceiveHit(Object* from, int damage);

    virtual void onGiveHit(Object* to, int damage);

    virtual bool isCollidable() const override { return getHp() > 0; }

    virtual bool isCharacter() const override { return true; }

    virtual void showStats() = 0;

protected:
    char m_ch;
    Color m_color;

    void setNextLevelXp();

    int m_hp;
    int m_maxHp;
    int m_xp;
    int m_gold;
    int m_nextLevelXp;
    int m_level;
    BehaviorNode* m_behavior;
    Blackboard* m_blackboard;
    Faction* m_faction;
    std::string m_name;

    ItemSharedPtrs m_items;
    ItemSharedPtrs m_equipped;

};

typedef std::shared_ptr<Character> CharacterPtr;
