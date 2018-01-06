#include "croom.h"
#include "crenderer.h"

Room::Room()
    : m_name()
    , m_surface()
{

}

void Room::setTilePtrSurface(const TilePtrSurface& surface)
{
    m_surface = surface;
}

void Room::setName(const String& name)
{
    m_name = name;
}

void Room::draw(Renderer* r)
{
    if (r->isVisible(this))
    {
        int rows = m_surface.size();
        for (int i = 0; i < rows; ++i)
        {
            const TilePtrs& row = m_surface[i];
            int cols = row.size();
            for (int j = 0; j < cols; ++j)
            {
                const Tile* t = row[j];
                r->draw(getX()+j, getY()+i, getZ(), t);
            }
        }
    }
}
