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
        mandatoryCharacters.push_back(CharacterTemplates::VILLAGER());

        Strings surface;
        surface.push_back("##########");
        surface.push_back("#........#");
        surface.push_back("#...--...#");
        surface.push_back("#........#");
        surface.push_back("####..####");

        r = RoomTemplateSharedPtr(new RoomTemplate(
            100,
            "Inn",
            surface,
            mandatoryCharacters,
            randomCharacters,
            0,
            4));
    }

    return r;
}
