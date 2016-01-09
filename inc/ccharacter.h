#pragma once

#include "cobject.h"
#include "ctile.h"
#include "cbehavior.h"

#include <string>

class Character : public Object
{
public:
    Character();

    virtual void draw(Renderer* r) override;

    virtual void tick(float dt) override;

    virtual void setBehavior(Behavior* behavior);

    const std::string& getName() const;

    void setName(const std::string& name);

    int getHp() const;

    void setHp(int hp);

    void setColor(Color color);

    void setStyle(ColorStyle style);

    void setChar(char ch);

protected:
    Tile m_tile;
    int m_hp;
    Behavior* m_behavior;
    std::string m_name;
};
