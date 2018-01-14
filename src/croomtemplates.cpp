#include "croomtemplates.h"
#include "ccharactertemplates.h"

const RoomTemplateSharedPtr& RoomTemplates::INN()
{
    static RoomTemplateSharedPtr r;
    if (!r)
    {
        CharacterTemplateSharedPtrs mandatoryCharacters;
        mandatoryCharacters.push_back(CharacterTemplates::VILLAGER());

        CharacterTemplateSharedPtrs randomCharacters;
        randomCharacters.push_back(CharacterTemplates::VILLAGER());

        RoomLayerTemplate floor1;
        floor1.push_back(CHAR_T("##########"));
        floor1.push_back(CHAR_T("#........#"));
        floor1.push_back(CHAR_T("#...--...#"));
        floor1.push_back(CHAR_T("#......_=#"));
        floor1.push_back(CHAR_T("####..####"));
        floor1.push_back(CHAR_T("   #||#   "));

        RoomLayerTemplate floor2;
        floor2.push_back(CHAR_T("##########"));
        floor2.push_back(CHAR_T("#........#"));
        floor2.push_back(CHAR_T("#.....##.#"));
        floor2.push_back(CHAR_T("#.....#  #"));
        floor2.push_back(CHAR_T("##########"));

        RoomLayerTemplate roof;
        roof.push_back(CHAR_T("##########"));
        roof.push_back(CHAR_T("##########"));
        roof.push_back(CHAR_T("##########"));
        roof.push_back(CHAR_T("##########"));
        roof.push_back(CHAR_T("##########"));

        RoomLayerTemplates layers;
        layers.push_back(floor1);
        layers.push_back(floor2);
        layers.push_back(roof);

        r = RoomTemplateSharedPtr(new RoomTemplate(
            100,
            CHAR_T("Inn"),
            layers,
            mandatoryCharacters,
            randomCharacters,
            1,
            4));
    }

    return r;
}

const RoomTemplateSharedPtr& RoomTemplates::DUNGEON_ROOM_LEFT()
{
    static RoomTemplateSharedPtr r;
    if (!r)
    {
        CharacterTemplateSharedPtrs mandatoryCharacters;
        CharacterTemplateSharedPtrs randomCharacters;

        RoomLayerTemplate floor;
        floor.push_back(CHAR_T("  #####   "));
        floor.push_back(CHAR_T("###...### "));
        floor.push_back(CHAR_T("#.......# "));
        floor.push_back(CHAR_T("#........x"));
        floor.push_back(CHAR_T("#.......# "));
        floor.push_back(CHAR_T("###...### "));
        floor.push_back(CHAR_T("  #####   "));

        RoomLayerTemplates layers;
        layers.push_back(floor);

        r = RoomTemplateSharedPtr(new RoomTemplate(
            100,
            CHAR_T("room1"),
            layers,
            mandatoryCharacters,
            randomCharacters,
            0,
            0));
    }

    return r;
}

const RoomTemplateSharedPtr& RoomTemplates::DUNGEON_ROOM_RIGHT()
{
    static RoomTemplateSharedPtr r;
    if (!r)
    {
        CharacterTemplateSharedPtrs mandatoryCharacters;
        CharacterTemplateSharedPtrs randomCharacters;

        RoomLayerTemplate floor;
        floor.push_back(CHAR_T("   #####  "));
        floor.push_back(CHAR_T(" ###...###"));
        floor.push_back(CHAR_T(" #.......#"));
        floor.push_back(CHAR_T("x........#"));
        floor.push_back(CHAR_T(" #.......#"));
        floor.push_back(CHAR_T(" ###...###"));
        floor.push_back(CHAR_T("   #####  "));

        RoomLayerTemplates layers;
        layers.push_back(floor);

        r = RoomTemplateSharedPtr(new RoomTemplate(
            100,
            CHAR_T("room1"),
            layers,
            mandatoryCharacters,
            randomCharacters,
            0,
            0));
    }

    return r;
}

const RoomTemplateSharedPtr& RoomTemplates::DUNGEON_ROOM_UP()
{
    static RoomTemplateSharedPtr r;
    if (!r)
    {
        CharacterTemplateSharedPtrs mandatoryCharacters;
        CharacterTemplateSharedPtrs randomCharacters;

        RoomLayerTemplate floor;
        floor.push_back(CHAR_T("    x    "));
        floor.push_back(CHAR_T("  ## ##  "));
        floor.push_back(CHAR_T("###...###"));
        floor.push_back(CHAR_T("#.......#"));
        floor.push_back(CHAR_T("#.......#"));
        floor.push_back(CHAR_T("#.......#"));
        floor.push_back(CHAR_T("###...###"));
        floor.push_back(CHAR_T("  #####  "));

        RoomLayerTemplates layers;
        layers.push_back(floor);

        r = RoomTemplateSharedPtr(new RoomTemplate(
            100,
            CHAR_T("room1"),
            layers,
            mandatoryCharacters,
            randomCharacters,
            0,
            0));
    }

    return r;
}

const RoomTemplateSharedPtr& RoomTemplates::DUNGEON_ROOM_DOWN()
{
    static RoomTemplateSharedPtr r;
    if (!r)
    {
        CharacterTemplateSharedPtrs mandatoryCharacters;
        CharacterTemplateSharedPtrs randomCharacters;

        RoomLayerTemplate floor;
        floor.push_back(CHAR_T("  #####  "));
        floor.push_back(CHAR_T("###...###"));
        floor.push_back(CHAR_T("#.......#"));
        floor.push_back(CHAR_T("#.......#"));
        floor.push_back(CHAR_T("#.......#"));
        floor.push_back(CHAR_T("###...###"));
        floor.push_back(CHAR_T("  ## ##  "));
        floor.push_back(CHAR_T("    x    "));

        RoomLayerTemplates layers;
        layers.push_back(floor);

        r = RoomTemplateSharedPtr(new RoomTemplate(
            100,
            CHAR_T("room1"),
            layers,
            mandatoryCharacters,
            randomCharacters,
            0,
            0));
    }

    return r;
}

const RoomTemplateSharedPtr& RoomTemplates::DUNGEON_CROSS()
{
    static RoomTemplateSharedPtr r;
    if (!r)
    {
        CharacterTemplateSharedPtrs mandatoryCharacters;
        CharacterTemplateSharedPtrs randomCharacters;

        RoomLayerTemplate floor;
        floor.push_back(CHAR_T("  x  "));
        floor.push_back(CHAR_T(" #.# "));
        floor.push_back(CHAR_T("x...x"));
        floor.push_back(CHAR_T(" #.# "));
        floor.push_back(CHAR_T("  x  "));

        RoomLayerTemplates layers;
        layers.push_back(floor);

        r = RoomTemplateSharedPtr(new RoomTemplate(
            100,
            CHAR_T("room1"),
            layers,
            mandatoryCharacters,
            randomCharacters,
            0,
            0));
    }

    return r;
}

const RoomTemplateSharedPtr& RoomTemplates::DUNGEON_TEE_LEFT()
{
    static RoomTemplateSharedPtr r;
    if (!r)
    {
        CharacterTemplateSharedPtrs mandatoryCharacters;
        CharacterTemplateSharedPtrs randomCharacters;

        RoomLayerTemplate floor;
        floor.push_back(CHAR_T("  x "));
        floor.push_back(CHAR_T(" #.#"));
        floor.push_back(CHAR_T("x..#"));
        floor.push_back(CHAR_T(" #.#"));
        floor.push_back(CHAR_T("  x "));

        RoomLayerTemplates layers;
        layers.push_back(floor);

        r = RoomTemplateSharedPtr(new RoomTemplate(
            100,
            CHAR_T("room1"),
            layers,
            mandatoryCharacters,
            randomCharacters,
            0,
            0));
    }

    return r;
}

const RoomTemplateSharedPtr& RoomTemplates::DUNGEON_TEE_RIGHT()
{
    static RoomTemplateSharedPtr r;
    if (!r)
    {
        CharacterTemplateSharedPtrs mandatoryCharacters;
        CharacterTemplateSharedPtrs randomCharacters;

        RoomLayerTemplate floor;
        floor.push_back(CHAR_T(" x  "));
        floor.push_back(CHAR_T("#.# "));
        floor.push_back(CHAR_T("#..x"));
        floor.push_back(CHAR_T("#.# "));
        floor.push_back(CHAR_T(" x  "));

        RoomLayerTemplates layers;
        layers.push_back(floor);

        r = RoomTemplateSharedPtr(new RoomTemplate(
            100,
            CHAR_T("room1"),
            layers,
            mandatoryCharacters,
            randomCharacters,
            0,
            0));
    }

    return r;
}

const RoomTemplateSharedPtr& RoomTemplates::DUNGEON_TEE_UP()
{
    static RoomTemplateSharedPtr r;
    if (!r)
    {
        CharacterTemplateSharedPtrs mandatoryCharacters;
        CharacterTemplateSharedPtrs randomCharacters;

        RoomLayerTemplate floor;
        floor.push_back(CHAR_T("  x  "));
        floor.push_back(CHAR_T(" #.# "));
        floor.push_back(CHAR_T("x...x"));
        floor.push_back(CHAR_T(" ### "));

        RoomLayerTemplates layers;
        layers.push_back(floor);

        r = RoomTemplateSharedPtr(new RoomTemplate(
            100,
            CHAR_T("room1"),
            layers,
            mandatoryCharacters,
            randomCharacters,
            0,
            0));
    }

    return r;
}

const RoomTemplateSharedPtr& RoomTemplates::DUNGEON_TEE_DOWN()
{
    static RoomTemplateSharedPtr r;
    if (!r)
    {
        CharacterTemplateSharedPtrs mandatoryCharacters;
        CharacterTemplateSharedPtrs randomCharacters;

        RoomLayerTemplate floor;
        floor.push_back(CHAR_T(" ### "));
        floor.push_back(CHAR_T("x...x"));
        floor.push_back(CHAR_T(" #.# "));
        floor.push_back(CHAR_T("  x  "));

        RoomLayerTemplates layers;
        layers.push_back(floor);

        r = RoomTemplateSharedPtr(new RoomTemplate(
            100,
            CHAR_T("room1"),
            layers,
            mandatoryCharacters,
            randomCharacters,
            0,
            0));
    }

    return r;
}

const RoomTemplateSharedPtr& RoomTemplates::DUNGEON_CORRIDOR_HORIZONTAL()
{
    static RoomTemplateSharedPtr r;
    if (!r)
    {
        CharacterTemplateSharedPtrs mandatoryCharacters;
        CharacterTemplateSharedPtrs randomCharacters;

        RoomLayerTemplate floor;
        floor.push_back(CHAR_T(" ###### "));
        floor.push_back(CHAR_T("x......x"));
        floor.push_back(CHAR_T(" ###### "));

        RoomLayerTemplates layers;
        layers.push_back(floor);

        r = RoomTemplateSharedPtr(new RoomTemplate(
            100,
            CHAR_T("room1"),
            layers,
            mandatoryCharacters,
            randomCharacters,
            0,
            0));
    }

    return r;
}

const RoomTemplateSharedPtr& RoomTemplates::DUNGEON_CORRIDOR_VERTICAL()
{
    static RoomTemplateSharedPtr r;
    if (!r)
    {
        CharacterTemplateSharedPtrs mandatoryCharacters;
        CharacterTemplateSharedPtrs randomCharacters;

        RoomLayerTemplate floor;
        floor.push_back(CHAR_T(" x "));
        floor.push_back(CHAR_T("#.#"));
        floor.push_back(CHAR_T("#.#"));
        floor.push_back(CHAR_T("#.#"));
        floor.push_back(CHAR_T("#.#"));
        floor.push_back(CHAR_T(" x"));

        RoomLayerTemplates layers;
        layers.push_back(floor);

        r = RoomTemplateSharedPtr(new RoomTemplate(
            100,
            CHAR_T("room1"),
            layers,
            mandatoryCharacters,
            randomCharacters,
            0,
            0));
    }

    return r;
}
