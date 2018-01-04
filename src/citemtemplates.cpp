#include "citemtemplates.h"
#include "cweapontemplate.h"
#include "ccolors.h"

const ItemTemplateSharedPtr& ItemTemplates::SWORD()
{
    static ItemTemplateSharedPtr w(
        new WeaponTemplate(100, CHAR_T("Sword"), 10, 70, Colors::NORMAL_GREY(), CHAR_T('|'), CHAR_T('-')));
    return w;
}

const ItemTemplateSharedPtr& ItemTemplates::PUNCH()
{
    static ItemTemplateSharedPtr w(
        new WeaponTemplate(100, CHAR_T("Punch"), 3, 7, Colors::SANDYELLOW(), CHAR_T('.'), CHAR_T('.')));
    return w;
}

const ItemTemplateSharedPtr& ItemTemplates::SPELL()
{
    static ItemTemplateSharedPtr w(
        new WeaponTemplate(50, CHAR_T("Spell"), 50, 80, Colors::YELLOW(), CHAR_T('*'), CHAR_T('*')));
    return w;
}

const ItemTemplateSharedPtr& ItemTemplates::CLAW()
{
    static ItemTemplateSharedPtr w(
        new WeaponTemplate(100, CHAR_T("Claw"), 10, 50, Colors::DARK_GREY(), CHAR_T('"'), CHAR_T('=')));
    return w;
}

const ItemTemplateSharedPtr& ItemTemplates::SNOWBALL()
{
    static ItemTemplateSharedPtr w(
        new WeaponTemplate(100, CHAR_T("Snowball"), 5, 6, Colors::WHITE(), CHAR_T('o'), CHAR_T('o')));
    return w;
}

const ItemTemplateSharedPtr& ItemTemplates::FIRE()
{
    static ItemTemplateSharedPtr w(
        new WeaponTemplate(100, CHAR_T("Fire"), 9, 9, Colors::ORANGE(), CHAR_T('s'), CHAR_T('~')));
    return w;
}
