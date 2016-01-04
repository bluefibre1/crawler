#include "ccharacter.h"
#include "crenderer.h"

Character::Character()
  : m_tile(ColorStyle::BRIGHT, Color::MAGENTA, Color::INVALID, '0')
{
  setFriction(1);
}

void Character::draw(Renderer* r)
{
  if (r->isVisible(this))
    {
      r->draw(getX(), getY(), getZ(), &m_tile);
    }
}

void Character::tick(float dt)
{
  Object::tick(dt);
}

