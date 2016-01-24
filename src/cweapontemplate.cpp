#include "cweapontemplate.h"


WeaponTemplate::WeaponTemplate(
    int probabilityWeight,
    const std::string& name,
    int minDamage,
    int maxDamage,
    const Color& color,
    char vch,
    char hch)
    : ItemTemplate(probabilityWeight, name)
    , m_minDamage(minDamage)
    , m_maxDamage(maxDamage)
    , m_color(color)
    , m_vch(vch)
    , m_hch(hch)
{

}
