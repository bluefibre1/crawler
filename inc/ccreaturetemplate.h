#pragma once

#include "ccolor.h"

#include <string>

class CreatureTemplate
{
public:

    CreatureTemplate(int probabylityWeight,
                     const std::string& name,
                     int minHp,
                     int maxHp,
                     float maxVelocity,
                     Color color,
                     ColorStyle style,
                     char ch/*,
                     const WeaponTemplate*[] weaponTemplates*/);

    int getProbabilityWeight() const { return m_probabilityWeight; }

    const std::string& getName() const { return m_name; }

    int getMinHp() const { return m_minHp; }

    int getMaxHp() const { return m_maxHp; }

    float getMaxVelocity() const { return m_maxVelocity; }

    Color getColor() const { return m_color; }

    ColorStyle getStyle() const { return m_style; }

    char getChar() const { return m_ch; }

private:
    int m_probabilityWeight;
    std::string m_name;
    int m_minHp;
    int m_maxHp;
    float m_maxVelocity;
    Color m_color;
    ColorStyle m_style;
    char m_ch;
};
