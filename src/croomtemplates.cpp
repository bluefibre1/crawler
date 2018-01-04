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

        Strings surface;
        surface.push_back(CHAR_T("##########"));
        surface.push_back(CHAR_T("#........#"));
        surface.push_back(CHAR_T("#...--...#"));
        surface.push_back(CHAR_T("#........#"));
        surface.push_back(CHAR_T("####..####"));

        r = RoomTemplateSharedPtr(new RoomTemplate(
            100,
            CHAR_T("Inn"),
            surface,
            mandatoryCharacters,
            randomCharacters,
            0,
            4));
    }

    return r;
}
