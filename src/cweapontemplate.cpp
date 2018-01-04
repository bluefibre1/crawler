#include "cweapontemplate.h"


WeaponTemplate::WeaponTemplate(
    int probabilityWeight,
    const String& name,
    int minDamage,
    int maxDamage,
    const Color& color,
    Char vch,
    Char hch)
    : ItemTemplate(probabilityWeight, name)
    , m_minDamage(minDamage)
    , m_maxDamage(maxDamage)
    , m_color(color)
    , m_vch(vch)
    , m_hch(hch)
{

}
