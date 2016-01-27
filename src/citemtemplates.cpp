#include "citemtemplates.h"
#include "cweapontemplate.h"
#include "ccolors.h"

const ItemTemplateSharedPtr& ItemTemplates::SWORD()
{
    static ItemTemplateSharedPtr w(
        new WeaponTemplate(100, "Sword", 10, 70, Colors::NORMAL_GREY(), '|', '-'));
    return w;
}

const ItemTemplateSharedPtr& ItemTemplates::PUNCH()
{
    static ItemTemplateSharedPtr w(
        new WeaponTemplate(100, "Punch", 3, 7, Colors::SANDYELLOW(), '.', '.'));
    return w;
}

const ItemTemplateSharedPtr& ItemTemplates::SPELL()
{
    static ItemTemplateSharedPtr w(
        new WeaponTemplate(50, "Spell", 50, 80, Colors::YELLOW(), '*', '*'));
    return w;
}

const ItemTemplateSharedPtr& ItemTemplates::CLAW()
{
    static ItemTemplateSharedPtr w(
        new WeaponTemplate(100, "Claw", 10, 50, Colors::DARK_GREY(), '"', '='));
    return w;
}

const ItemTemplateSharedPtr& ItemTemplates::SNOWBALL()
{
    static ItemTemplateSharedPtr w(
        new WeaponTemplate(100, "Snowball", 5, 6, Colors::WHITE(), 'o', 'o'));
    return w;
}

const ItemTemplateSharedPtr& ItemTemplates::FIRE()
{
    static ItemTemplateSharedPtr w(
        new WeaponTemplate(100, "Fire", 9, 9, Colors::ORANGE(), 's', '~'));
    return w;
}
