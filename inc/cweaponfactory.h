#pragma once

class Weapon;
class WeaponTemplate;

class WeaponFactory
{
public:

    static Weapon* create(const WeaponTemplate* t);

};
