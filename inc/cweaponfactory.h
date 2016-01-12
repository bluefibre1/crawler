#pragma once

#include "cweapon.h"

class WeaponTemplate;

class WeaponFactory
{
public:

    static WeaponPtr create(const WeaponTemplate* t);

};
