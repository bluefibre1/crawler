#pragma once

#include "citemtemplate.h"

class WeaponTemplate : public ItemTemplate
{
public:

    WeaponTemplate(
        int probabilityWeight,
        const String& name,
        int minDamage,
        int maxDamage,
        const Color& color,
        Char vch,
        Char hch);

    virtual Type getType() const { return Type::WEAPON; }

    int getMinDamage() const { return m_minDamage; }

    int getMaxDamage() const { return m_maxDamage; }

    const Color& getColor() const { return m_color; }

    Char getVerticalChar() const { return m_vch; }

    Char getHorizontalChar() const { return m_hch; }

private:
    int m_minDamage;
    int m_maxDamage;
    Color m_color;
    Char m_vch;
    Char m_hch;
};
