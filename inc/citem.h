#pragma once

#include "cobject.h"

#include <string>
#include <memory>

class Item : public Object
{
public:
    Item();

    void setName(const std::string& name);

    const std::string& getName() const;

    bool isEquipable() const { return m_isEquipable; }

    bool isUsable() const { return m_isUsable; }

    bool isWeapon() const { return m_isWeapon; }

    bool isArmor() const { return m_isArmor; }

protected:
    bool m_isEquipable;
    bool m_isUsable;
    bool m_isWeapon;
    bool m_isArmor;

private:
    std::string m_name;
};

typedef std::shared_ptr<Item> ItemPtr;
