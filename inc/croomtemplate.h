#pragma once

#include "ctile.h"
#include "cstring.h"
#include "ccharactertemplate.h"

typedef Strings RoomLayerTemplate;
typedef std::vector<RoomLayerTemplate> RoomLayerTemplates;

class RoomTemplate
{
public:
    RoomTemplate(
        int probabilityWeight,
        const String& name,
        const RoomLayerTemplates& layers,
        const CharacterTemplateSharedPtrs& mandatoryCharacters,
        const CharacterTemplateSharedPtrs& randomCharacters,
        int minRandomCharacters,
        int maxRandomCharacters);

    int getProbabilityWeight() const { return m_probabilityWeight; }
    const String& getName() const { return m_name; }
    const RoomLayerTemplates& getLayers() const { return m_layers; }
    const CharacterTemplateSharedPtrs& getMandatoryCharacters() const { return m_mandatoryCharacters; }
    const CharacterTemplateSharedPtrs& getRandomCharacters() const { return m_randomCharacters; }
    int getMinRandomCharacters() const { return m_minRandomCharacters; }
    int getMaxRandomCharacters() const { return m_maxRandomCharacters; }

private:
    int m_probabilityWeight;
    String m_name;
    RoomLayerTemplates m_layers;
    CharacterTemplateSharedPtrs m_mandatoryCharacters;
    CharacterTemplateSharedPtrs m_randomCharacters;
    int m_minRandomCharacters;
    int m_maxRandomCharacters;
};

typedef std::shared_ptr<RoomTemplate> RoomTemplateSharedPtr;
