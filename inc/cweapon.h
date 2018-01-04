#pragma once

#include "citem.h"
#include "ctimer.h"
#include "ccolor.h"

class Weapon : public Item
{
public:
    Weapon();

    void setDamage(int value);

    int getDamage() const;

    void setVerticalChar(Char c);

    void setHorizontalChar(Char c);

    void setColor(const Color& color);

    virtual void draw(Renderer* r) override;

    virtual void use(Direction dir) override;

private:
    void show();
    void getDeltas(float& dx, float& dy);

    Direction m_dir;
    int m_damage;
    Char m_verticalChar;
    Char m_horizontalChar;
    Color m_color;
    bool m_visible;
    Timer m_showTimer;
};

typedef std::shared_ptr<Weapon> WeaponPtr;
