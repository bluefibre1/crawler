#pragma once

#include "citem.h"

class Weapon : public Item
{
public:
    Weapon();

private:
    int m_damage;
};
