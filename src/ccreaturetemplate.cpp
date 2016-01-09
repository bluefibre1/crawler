#include "ccreaturetemplate.h"

CreatureTemplate::CreatureTemplate(const std::string& name,
                                   int minHp,
                                   int maxHp,
                                   float maxVelocity,
                                   Color color,
                                   ColorStyle style,
                                   char ch)
    : m_name(name)
    , m_minHp(minHp)
    , m_maxHp(maxHp)
    , m_maxVelocity(maxVelocity)
    , m_color(color)
    , m_style(style)
    , m_ch(ch)
{

}
