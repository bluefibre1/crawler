#include "chero.h"
#include "cinput.h"

#include <stdlib.h>

const float HERO_VELOCITY = 1;

Hero::Hero()
{
  m_tile = Tile(ColorStyle::BRIGHT, Color::MAGENTA, Color::INVALID, '0');
}

void Hero::tick(float dt)
{
  int key;
  if (Input::getKey(key))
    {
      switch (key)
	{
	case (int)Key::UP:
	  setVelocity(0, -HERO_VELOCITY/dt, 0);
	  break;

	case (int)Key::DOWN:
	  setVelocity(0, HERO_VELOCITY/dt, 0);
	  break;

	case (int)Key::LEFT:
	  setVelocity(-HERO_VELOCITY/dt, 0, 0);
	  break;

	case (int)Key::RIGHT:
	  setVelocity(HERO_VELOCITY/dt, 0, 0);
	  break;

	case 'q':
	case 'Q':
	  Input::setQuit();
	  break;
	}      
    }

  Character::tick(dt);
}
