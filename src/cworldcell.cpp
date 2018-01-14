#include "cworldcell.h"

#include <assert.h>

WorldCell::WorldCell()
    : m_room(nullptr)
    , m_over(nullptr)
    , m_under(nullptr)
    , m_tile(nullptr)
    , m_z(INT_MIN)
{

}

void WorldCell::setUnder(WorldCell* under)
{
    assert(under);
    assert(!m_under);
    m_under = under;
    assert(!under->m_over);
    under->m_over = this;
}

WorldCell* WorldCell::getTop()
{
    WorldCell* c = this;
    while (c->m_over)
    {
        c = c->m_over;
    }
    return c;
}

WorldCell* WorldCell::getBottom()
{
    WorldCell* c = this;
    while (c->m_under)
    {
        c = c->m_under;
    }
    return c;
}

int WorldCell::getHeight() const
{
    return m_tile ? m_tile->getHeight() : 0;
}
