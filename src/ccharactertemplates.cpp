#include "ccharactertemplates.h"
#include "citemtemplates.h"
#include "cfactions.h"
#include "ccolors.h"

const CharacterTemplateSharedPtr& CharacterTemplates::DEMON()
{
    ItemTemplateSharedPtrs items;
    items.push_back(ItemTemplates::HOOK());
    items.push_back(ItemTemplates::SPELL());

    static CharacterTemplateSharedPtr c(
        new CharacterTemplate(10, CHAR_T("Demon"), 10, 20, Colors::RED(), CHAR_T('D'), Factions::DRAGON(), items));
    return c;
}

const CharacterTemplateSharedPtr& CharacterTemplates::BAT()
{
    ItemTemplateSharedPtrs items;
    items.push_back(ItemTemplates::CLAW());

    static CharacterTemplateSharedPtr c(
        new CharacterTemplate(50, CHAR_T("Bat"), 5, 5, Colors::BLACK(), CHAR_T('b'), Factions::WILDERNESS(), items));
    return c;
}

const CharacterTemplateSharedPtr& CharacterTemplates::VILLAGER()
{
    ItemTemplateSharedPtrs items;
    items.push_back(ItemTemplates::SNOWBALL());
    items.push_back(ItemTemplates::SWORD());

    static CharacterTemplateSharedPtr c(
        new CharacterTemplate(100, CHAR_T("Villager"), 15, 25, Colors::LIGHT_BLUE(), CHAR_T('V'), Factions::DEFAULT(), items));
    return c;
}

const CharacterTemplateSharedPtr& CharacterTemplates::KID()
{
    ItemTemplateSharedPtrs items;
    items.push_back(ItemTemplates::SNOWBALL());

    static CharacterTemplateSharedPtr c(
        new CharacterTemplate(100, CHAR_T("Kid"), 1, 2, Colors::LIGHT_BLUE(), CHAR_T('v'), Factions::WILDERNESS(), items));
    return c;
}

