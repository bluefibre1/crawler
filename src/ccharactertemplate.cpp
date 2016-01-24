#include "ccharactertemplate.h"

CharacterTemplate::CharacterTemplate(
    int probabilityWeight,
    const String& name,
    int minHp,
    int maxHp,
    Color color,
    char ch,
    const FactionSharedPtr& faction,
    const ItemTemplateSharedPtrs& itemTemplates)
    : m_probabilityWeight(probabilityWeight)
    , m_name(name)
    , m_minHp(minHp)
    , m_maxHp(maxHp)
    , m_color(color)
    , m_ch(ch)
    , m_faction(faction)
    , m_itemTemplates(itemTemplates)
{

}
