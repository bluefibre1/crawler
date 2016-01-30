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
        const Strings& surface,
        const CharacterTemplateSharedPtrs& mandatoryCharacters,
        const CharacterTemplateSharedPtrs& randomCharacters,
        int minRandomCharacters,
        int maxRandomCharacters);

    int getProbabilityWeight() const { return m_probabilityWeight; }
    const String& getName() const { return m_name; }
    const Strings& getSurface() const { return m_surface; }
    const CharacterTemplateSharedPtrs& getMandatoryCharacters() const { return m_mandatoryCharacters; }
    const CharacterTemplateSharedPtrs& getRandomCharacters() const { return m_randomCharacters; }
    int getMinRandomCharacters() const { return m_minRandomCharacters; }
    int getMaxRandomCharacters() const { return m_maxRandomCharacters; }

private:
    int m_probabilityWeight;
    String m_name;
    Strings m_surface;
    CharacterTemplateSharedPtrs m_mandatoryCharacters;
    CharacterTemplateSharedPtrs m_randomCharacters;
    int m_minRandomCharacters;
    int m_maxRandomCharacters;
};

typedef std::shared_ptr<RoomTemplate> RoomTemplateSharedPtr;
