#include "chero.h"
#include "cinput.h"

#include <stdlib.h>

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
	  setVelocity(0, -1/dt, 0);
	  break;

	case (int)Key::DOWN:
	  setVelocity(0, 1/dt, 0);
	  break;

	case (int)Key::LEFT:
	  setVelocity(-1/dt, 0, 0);
	  break;

	case (int)Key::RIGHT:
	  setVelocity(1/dt, 0, 0);
	  break;

	case 'q':
	case 'Q':
	  Input::setQuit();
	  break;
	}      
    }

  Character::tick(dt);
}
