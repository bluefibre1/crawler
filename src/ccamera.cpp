#include "ccamera.h"

#include "crenderer.h"

void Camera::draw(Renderer* r)
{
    if (!m_subject)
    {
        return;
    }

    // control camera around hero
    int centerX = m_subject->getX() - r->getWidth() / 2;
    int centerY = m_subject->getY() - r->getHeight() / 2;
    int centerZ = m_subject->getZ();
    /*
      int ox = r.getOriginX();
      int oy = r.getOriginY();
      int errX = (int)fabs((float)centerX - ox) - r.getWidth() / 6;
      int errY = (int)fabs((float)centerY - oy) - r.getHeight() / 6;
      if (errX > 0)
      {
      ox += (centerX > ox) ? errX : -errX;
      }

      if (errY > 0)
      {
      oy += (centerY > oy) ? errY : -errY;
      }

      r.setOrigin(ox, oy);
    */
    r->setOrigin(centerX, centerY, centerZ);
    r->clear();
}
