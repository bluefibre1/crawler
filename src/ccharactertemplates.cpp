#include "ccharactertemplates.h"
#include "citemtemplates.h"
#include "ccolors.h"

const CharacterTemplateSharedPtr& CharacterTemplates::DRAGON()
{
    ItemTemplateSharedPtrs items;
    items.push_back(ItemTemplates::FIRE());
    items.push_back(ItemTemplates::CLAW());

    static CharacterTemplateSharedPtr c(
        new CharacterTemplate(10, "Dragon", 10, 20, Colors::RED(), 'D', items));
    return c;
}

const CharacterTemplateSharedPtr& CharacterTemplates::BAT()
{
    ItemTemplateSharedPtrs items;
    items.push_back(ItemTemplates::CLAW());

    static CharacterTemplateSharedPtr c(
        new CharacterTemplate(50, "Bat", 5, 5, Colors::BLACK(), 'b', items));
    return c;
}

const CharacterTemplateSharedPtr& CharacterTemplates::VILLAGER()
{
    ItemTemplateSharedPtrs items;
    items.push_back(ItemTemplates::SNOWBALL());
    items.push_back(ItemTemplates::PUNCH());

    static CharacterTemplateSharedPtr c(
        new CharacterTemplate(100, "Villager", 15, 25, Colors::LIGHT_BLUE(), 'V', items));
    return c;
}

const CharacterTemplateSharedPtr& CharacterTemplates::KID()
{
    ItemTemplateSharedPtrs items;
    items.push_back(ItemTemplates::SNOWBALL());

    static CharacterTemplateSharedPtr c(
        new CharacterTemplate(100, "Kid", 1, 2, Colors::LIGHT_BLUE(), 'v', items));
    return c;
}

