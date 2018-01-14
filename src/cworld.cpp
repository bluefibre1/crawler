#include "cworld.h"

#include "ctiles.h"
#include "crenderer.h"
#include "ccamera.h"

#include <assert.h>

World::World()
    : m_rooms()
    , m_cells()
    , m_width(0)
    , m_height(0)
{
}

void World::addOnTop(int x, int y, const RoomSharedPtr& room)
{
    m_rooms.push_back(room);
    if (m_cells.empty())
    {
        m_width = room->getWidth();
        m_height = room->getHeight();
        int n = m_width * m_height;
        assert(n > 0);
        m_cells.resize(n);
        for (int i = 0; i < n; ++i)
        {
            m_cells[i] = &room->getCells()[i];
        }
    }
    else
    {
        assert(x + room->getWidth() < m_width);
        assert(y + room->getHeight() < m_height);

        for (int oy = 0; oy < room->getHeight(); ++oy)
        {
            for (int ox = 0; ox < room->getWidth(); ++ox)
            {
                int ri = ox + oy * room->getWidth();
                int wi = x + ox + (y + oy) * m_width;
                assert(wi < (int)m_cells.size());

                auto bottom = &room->getCells()[ri];
                auto top = bottom->getTop();

                auto ground = m_cells[wi];
                bottom->setUnder(ground);
                m_cells[wi] = top;
                int z = ground->getZ() + ground->getSmook();

                auto i = bottom;
                do
                {
                    i->setZ(i->getZ() + z);
                    i = i->getOver();
                }
                while (i);
            }
        }
    }
}

int World::getHeightAt(int x, int y, int z) const
{
    assert(x >= 0 && x < getWidth());
    assert(y >= 0 && y < getHeight());
    int i = x + y * getWidth();
    WorldCell* c = m_cells[i];
    while (z < c->getZ() && c->getUnder())
    {
        c = c->getUnder();
    }
    return c->getZ() + c->getSmook();
}

Object* World::getRoom(int x, int y, int z) const
{
    assert(x >= 0 && x < getWidth());
    assert(y >= 0 && y < getHeight());
    int i = x + y * getWidth();
    WorldCell* c = m_cells[i];
    while (z < c->getZ() && c->getUnder())
    {
        c = c->getUnder();
    }
    return c->getRoom();
}

void World::draw(Camera* c, Renderer* r)
{
    int ox = r->getOriginX();
    int oy = r->getOriginY();
    int w = r->getWidth() + ox;
    int h = r->getHeight() + oy;

    Object* subjectRoom = c->getSubject() ? c->getSubject()->getRoom() : nullptr;
    int subjectZ = 0;

    for (int y = oy; y < h; y++)
    {
        if (y < 0 || y >= getHeight())
        {
            continue;
        }

        for (int x = ox; x < w; x++)
        {
            if (x < 0 || x >= getWidth())
            {
                continue;
            }
            int idx = x + y * getWidth();
            const WorldCell* c = m_cells[idx];
            while (!c->getTile())
            {
                c = c->getUnder();
            }

            if (c->getTile())
            {
                if (c->getRoom() == subjectRoom)
                {
                    while (subjectZ < c->getZ() &&
                           c->getUnder() &&
                           c->getUnder()->getRoom() == subjectRoom)
                    {
                        c = c->getUnder();
                    }
                }

                r->draw(x, y, c->getZ(), c->getTile());
            }
        }
    }
}

