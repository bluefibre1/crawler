#pragma once

#include "ctile.h"
#include "cstring.h"
#include "ccharactertemplate.h"

class RoomTemplate
{
public:
    RoomTemplate(
        int probabilityWeight,
        const String& name,
        const TilePtrSurface& surface,
        const CharacterTemplateSharedPtrs& mandatoryCharacters,
        const CharacterTemplateSharedPtrs& randomCharacters);

private:
    int m_probabilityWeight;
    String m_name;
    TilePtrSurface m_surface;
    CharacterTemplateSharedPtrs m_mandatoryCharacters;
    CharacterTemplateSharedPtrs m_randomCharacters;
};
