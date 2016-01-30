#pragma once

#include "cobject.h"
#include "ccolor.h"
#include "citem.h"
#include "cdirection.h"
#include "cwindow.h"
#include "cfaction.h"

class BehaviorNode;
class Blackboard;

class Character : public Object
{
public:
    Character();
    ~Character();

    virtual void draw(Renderer* r) override;

    virtual void tick(float dt) override;

    void setBehavior(BehaviorNode* behavior);

    void setBlackboard(Blackboard* blackboard);

    void setFaction(const FactionSharedPtr& faction);

    const FactionSharedPtr& getFaction() const;

    const String& getName() const;

    void setName(const String& name);

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

    virtual int getObjectType() const override { return OBJECT_TYPE_CHARACTER; }

    virtual void showStats();

    void debugStringAppend(const String& value);

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
    int m_lastTickFrameId;
    String m_debugString;
    BehaviorNode* m_behavior;
    Blackboard* m_blackboard;
    FactionSharedPtr m_faction;
    String m_name;

    ItemSharedPtrs m_items;
    ItemSharedPtrs m_equipped;

    WindowWeakPtr m_statsPopup;
};

typedef std::shared_ptr<Character> CharacterSharedPtr;
