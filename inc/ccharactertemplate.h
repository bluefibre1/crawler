#pragma once

#include "ccolor.h"
#include "citemtemplates.h"
#include "cfaction.h"
#include "cstring.h"


class CharacterTemplate
{
public:

    CharacterTemplate(
        int probabylityWeight,
        const String& name,
        int minHp,
        int maxHp,
        Color color,
        char ch,
        const FactionSharedPtr& faction,
        const ItemTemplateSharedPtrs& itemTemplates);

    int getProbabilityWeight() const { return m_probabilityWeight; }

    const String& getName() const { return m_name; }

    int getMinHp() const { return m_minHp; }

    int getMaxHp() const { return m_maxHp; }

    Color getColor() const { return m_color; }

    char getChar() const { return m_ch; }

    const FactionSharedPtr& getFaction() const { return m_faction; }

    const ItemTemplateSharedPtrs& getItemTemplates() const { return m_itemTemplates; }

private:
    int m_probabilityWeight;
    String m_name;
    int m_minHp;
    int m_maxHp;
    Color m_color;
    char m_ch;
    FactionSharedPtr m_faction;
    ItemTemplateSharedPtrs m_itemTemplates;
};

typedef std::shared_ptr<CharacterTemplate> CharacterTemplateSharedPtr;
typedef std::vector<CharacterTemplateSharedPtr> CharacterTemplateSharedPtrs;
