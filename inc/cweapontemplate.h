#pragma once

#include "citemtemplate.h"

class WeaponTemplate : public ItemTemplate
{
public:

    WeaponTemplate(
        int probabilityWeight,
        const std::string& name,
        int minDamage,
        int maxDamage,
        const Color& color,
        char vch,
        char hch);

    virtual Type getType() const { return Type::WEAPON; }

    int getMinDamage() const { return m_minDamage; }

    int getMaxDamage() const { return m_maxDamage; }

    const Color& getColor() const { return m_color; }

    char getVerticalChar() const { return m_vch; }

    char getHorizontalChar() const { return m_hch; }

private:
    int m_minDamage;
    int m_maxDamage;
    float m_maxVelocity;
    Color m_color;
    char m_vch;
    char m_hch;
};
