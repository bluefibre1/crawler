#pragma once

#include "citem.h"

class Weapon : public Item
{
public:
    Weapon();

    void setDamage(int value);

    int getDamage() const;

    virtual void use(Object* source, Direction dir) override;

private:
    int m_damage;
};

typedef std::shared_ptr<Weapon> WeaponPtr;
