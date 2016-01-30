#include "croomtemplate.h"


RoomTemplate::RoomTemplate(
    int probabilityWeight,
    const String& name,
    const Strings& surface,
    const CharacterTemplateSharedPtrs& mandatoryCharacters,
    const CharacterTemplateSharedPtrs& randomCharacters,
    int minRandomCharacters,
    int maxRandomCharacters)
    : m_probabilityWeight(probabilityWeight)
    , m_name(name)
    , m_surface(surface)
    , m_mandatoryCharacters(mandatoryCharacters)
    , m_randomCharacters(randomCharacters)
    , m_minRandomCharacters(minRandomCharacters)
    , m_maxRandomCharacters(maxRandomCharacters)
{

}
