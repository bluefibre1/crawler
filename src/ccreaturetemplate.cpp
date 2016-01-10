#include "ccreaturetemplate.h"

CreatureTemplate::CreatureTemplate(const std::string& name,
                                   int minHp,
                                   int maxHp,
                                   float maxVelocity,
                                   Color color,
                                   char ch)
    : m_name(name)
    , m_minHp(minHp)
    , m_maxHp(maxHp)
    , m_maxVelocity(maxVelocity)
    , m_color(color)
    , m_ch(ch)
{

}
