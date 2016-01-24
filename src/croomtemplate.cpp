#include "croomtemplate.h"


RoomTemplate::RoomTemplate(
    int probabilityWeight,
    const String& name,
    const TilePtrSurface& surface,
    const CharacterTemplateSharedPtrs& mandatoryCharacters,
    const CharacterTemplateSharedPtrs& randomCharacters)
    : m_probabilityWeight(probabilityWeight)
    , m_name(name)
    , m_mandatoryCharacters(mandatoryCharacters)
    , m_randomCharacters(randomCharacters)
{

}
