#pragma once

#include "cobject.h"
#include "ccolor.h"
#include "citem.h"

#include <string>
#include <vector>

class Item;
class Behavior;

class Character : public Object
{
public:
    Character();

    virtual void draw(Renderer* r) override;

    virtual void tick(float dt) override;

    virtual void setBehavior(Behavior* behavior);

    const std::string& getName() const;

    void setName(const std::string& name);

    int getHp() const;

    void setHp(int hp);

    void setColor(const Color& color);

    void setChar(char ch);

    void addItem(const ItemPtr& item);

    void removeItem(const ItemPtr& item);

    void equip(const ItemPtr& item);

    void unequip(const ItemPtr& item);

protected:
    char m_ch;
    Color m_color;
    int m_hp;
    Behavior* m_behavior;
    std::string m_name;

    typedef std::vector<ItemPtr> Items;
    Items m_items;
    Items m_equipped;

};

typedef std::shared_ptr<Character> CharacterPtr;
