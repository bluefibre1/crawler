#pragma once

#include "ccolor.h"

#include <string>

class WeaponTemplate
{
public:

    WeaponTemplate(int probabylityWeight,
                   const std::string& name,
                   int minDamage,
                   int maxDamage,
                   Color color,
                   ColorStyle style,
                   char vch,
                   char hch);

    int getProbabilityWeight() const { return m_probabilityWeight; }

    const std::string& getName() const { return m_name; }

    int getMinDamage() const { return m_minDamage; }

    int getMaxDamage() const { return m_maxDamage; }

    Color getColor() const { return m_color; }

    ColorStyle getStyle() const { return m_style; }

    char getVerticalChar() const { return m_vch; }

    char getHorizontalChar() const { return m_hch; }

private:
    int m_probabilityWeight;
    std::string m_name;
    int m_minDamage;
    int m_maxDamage;
    float m_maxVelocity;
    Color m_color;
    ColorStyle m_style;
    char m_vch;
    char m_hch;
};
