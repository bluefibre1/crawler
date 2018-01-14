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

        RoomLayerTemplate rc;
        rc.push_back(CHAR_T("##########"));
        rc.push_back(CHAR_T("#........#"));
        rc.push_back(CHAR_T("#...--...#"));
        rc.push_back(CHAR_T("#........#"));
        rc.push_back(CHAR_T("####||####"));

        RoomLayerTemplate roof;
        roof.push_back(CHAR_T("##########"));
        roof.push_back(CHAR_T("##########"));
        roof.push_back(CHAR_T("##########"));
        roof.push_back(CHAR_T("##########"));
        roof.push_back(CHAR_T("####  ####"));

        RoomLayerTemplates layers;
        layers.push_back(rc);
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
