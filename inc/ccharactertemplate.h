#pragma once

#include "ccolor.h"
#include "citemtemplates.h"
#include "cstring.h"


class CharacterTemplate
{
public:

    CharacterTemplate(int probabylityWeight,
                     const std::string& name,
                     int minHp,
                     int maxHp,
                     Color color,
                     char ch,
                     const ItemTemplateSharedPtrs& itemTemplates);

    int getProbabilityWeight() const { return m_probabilityWeight; }

    const std::string& getName() const { return m_name; }

    int getMinHp() const { return m_minHp; }

    int getMaxHp() const { return m_maxHp; }

    Color getColor() const { return m_color; }

    char getChar() const { return m_ch; }

    const ItemTemplateSharedPtrs& getItemTemplates() const { return m_itemTemplates; }

private:
    int m_probabilityWeight;
    std::string m_name;
    int m_minHp;
    int m_maxHp;
    Color m_color;
    char m_ch;
    ItemTemplateSharedPtrs m_itemTemplates;
};

typedef std::shared_ptr<CharacterTemplate> CharacterTemplateSharedPtr;
typedef std::vector<CharacterTemplateSharedPtr> CharacterTemplateSharedPtrs;
