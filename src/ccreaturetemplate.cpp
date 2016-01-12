#include "ccreaturetemplate.h"

CreatureTemplate::CreatureTemplate(int probabilityWeight,
                                   const std::string& name,
                                   int minHp,
                                   int maxHp,
                                   float maxVelocity,
                                   Color color,
                                   char ch,
                                   const std::vector<const WeaponTemplate*>& weaponTemplates)
    : m_probabilityWeight(probabilityWeight)
    , m_name(name)
    , m_minHp(minHp)
    , m_maxHp(maxHp)
    , m_maxVelocity(maxVelocity)
    , m_color(color)
    , m_ch(ch)
    , m_weaponTemplates(weaponTemplates)
{

}
