#include "citemtemplates.h"
#include "cweapontemplate.h"
#include "ccolors.h"

const ItemTemplateSharedPtr& ItemTemplates::SWORD()
{
    static ItemTemplateSharedPtr w(
        new WeaponTemplate(100, "Sword", 3, 7, Colors::NORMAL_GREY(), '|', '-'));
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
        new WeaponTemplate(50, "Spell", 5, 8, Colors::YELLOW(), '*', '*'));
    return w;
}

const ItemTemplateSharedPtr& ItemTemplates::CLAW()
{
    static ItemTemplateSharedPtr w(
        new WeaponTemplate(100, "Claw", 1, 5, Colors::DARK_GREY(), '"', '='));
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
        new WeaponTemplate(100, "Fire", 5, 7, Colors::ORANGE(), 's', '~'));
    return w;
}
