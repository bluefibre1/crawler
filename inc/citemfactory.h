#pragma once

#include "citemtemplate.h"
#include "citem.h"

class WeaponTemplate;
class PotionTemplate;

class ItemFactory
{
public:

    static ItemSharedPtr create(const ItemTemplateSharedPtr& t);

private:
    static ItemSharedPtr createWeapon(const WeaponTemplate* t);
    static ItemSharedPtr createPotion(const PotionTemplate* t);
};
