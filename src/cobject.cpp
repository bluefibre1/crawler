#include "cobject.h"
#include "csimulator.h"

Object::Object()
  : m_x(0)
  , m_y(0)
  , m_z(0)
  , m_velX(0)
  , m_velY(0)
  , m_velZ(0)
  , m_friction(0)
{

}

void Object::tick(float dt)
{
  if (m_velX != 0 || m_velY != 0 || m_velZ != 0)
    {
      Simulator::get()->activate(this);
    }
}
