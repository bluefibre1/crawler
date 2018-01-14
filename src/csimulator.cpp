#include "csimulator.h"
#include "cmath.h"
#include "crenderer.h"

#include <stdio.h>
#include <float.h>
#include <assert.h>

static const int MAX_STEP = 1;

Simulator::Simulator()
    : m_cellSize(30)
    , m_cellNumX(0)
    , m_cellNumY(0)
    , m_viewPortX(0)
    , m_viewPortY(0)
    , m_viewPortWidth(0)
    , m_viewPortHeight(0)
    , m_cells()
    , m_world()
    , m_removed()
    , m_activated()
{

}

Simulator& Simulator::get()
{
    static Simulator instance;
    return instance;
}

void Simulator::setWorld(const WorldSharedPtr& world)
{
    m_world = world;
    initCell();
}

void Simulator::add(const ObjectSharedPtr& object)
{
    int idx = getCellIndex(object->getX(), object->getY());
    assert(idx < (int)m_cells.size());
    assert(idx >= 0);
    ObjectSharedPtrs& objs = m_cells[idx];
    if (objs.size() + 1 >= objs.capacity())
    {
        objs.reserve((int)(objs.size() * 1.5f)+1);
    }
    objs.push_back(object);
}

void Simulator::spawn(const ObjectSharedPtr& object)
{
    while (true)
    {
        int x = Math::ceilRandom(m_world->getWidth());
        int y = Math::ceilRandom(m_world->getHeight());
        int z = m_world->getHeightAt(x, y, INT_MAX);

        if (!isColliding(object.get(), x, y, z))
        {
            object->setPosition(x,y,z);
            break;
        }
    }

    add(object);
}

void Simulator::remove(Object* object)
{
    m_removed.push_back(object);
}

void Simulator::activate(Object* object)
{
    m_activated.push_back(object);
}

void Simulator::tick(float dt)
{
    int cellIndex = getCellIndex(m_viewPortX, m_viewPortY);
    int cellCols  = m_viewPortWidth / m_cellSize + 2;
    int cellRows  = m_viewPortHeight / m_cellSize + 2;

    for (int cellY = 0; cellY < cellRows; cellY++)
    {
        for (int cellX = 0; cellX < cellCols; cellX++)
        {
            int idx = cellIndex + cellX + cellY * m_cellNumX;
            if (idx >= 0 && idx < (int)m_cells.size())
            {
                ObjectSharedPtrs& objs = m_cells[idx];
                for (auto i = objs.begin(); i != objs.end(); ++i)
                {
                    (*i)->tick(dt);
                }
            }
        }
    }

    for (auto i = m_activated.begin(); i != m_activated.end(); ++i)
    {
        Object* collidee = *i;

        int newX = collidee->getX() + collidee->getDisplacementX();
        int newY = collidee->getY() + collidee->getDisplacementY();
        int newZ = collidee->getZ();

        Math::clamp(newX, 0, m_world->getWidth() - 1);
        Math::clamp(newY, 0, m_world->getHeight() - 1);

        if (!isColliding(collidee, newX, newY, newZ))
        {
            int oldCellIndex = getCellIndex(collidee->getX(), collidee->getY());
            int newCellIndex = getCellIndex(newX, newY);

            if (oldCellIndex != newCellIndex)
            {
                assert(oldCellIndex < (int)m_cells.size());
                assert(newCellIndex < (int)m_cells.size());
                ObjectSharedPtrs& oldCell = m_cells[oldCellIndex];
                auto it = std::find_if(
                    oldCell.begin(), oldCell.end(), [collidee](const ObjectSharedPtr& other)
                    {
                        return other.get() == collidee;
                    });
                assert(it != oldCell.end());
                ObjectSharedPtr obj = *it;
                oldCell.erase(it);

                ObjectSharedPtrs& newCell = m_cells[newCellIndex];
                newCell.push_back(obj);
            }

            collidee->setPosition(newX, newY, newZ);
            collidee->setRoom(m_world->getRoom(newX, newY, newZ));
        }

        collidee->stop();
    }

    m_activated.clear();

    for (auto i = m_removed.begin(); i != m_removed.end(); ++i)
    {
        Object* obj = *i;
        int cellIndex = getCellIndex(obj->getX(), obj->getY());
        assert(cellIndex < (int)m_cells.size());
        ObjectSharedPtrs& cell = m_cells[cellIndex];

        auto it = std::find_if(
            cell.begin(), cell.end(), [obj](const ObjectSharedPtr& other)
            {
                return other.get() == obj;
            });

        assert(it != cell.end());
        if (it != cell.end())
        {
            cell.erase(it);
        }
    }
}

void Simulator::draw(Camera* c, Renderer* r)
{
    m_viewPortX = r->getOriginX();
    m_viewPortY = r->getOriginY();
    m_viewPortWidth = r->getWidth();
    m_viewPortHeight = r->getHeight();

    m_world->draw(c, r);
    int cellIndex = getCellIndex(m_viewPortX, m_viewPortY);
    int cellCols  = m_viewPortWidth / m_cellSize + 2;
    int cellRows  = m_viewPortHeight / m_cellSize + 2;

    for (int cellY = 0; cellY < cellRows; cellY++)
    {
        for (int cellX = 0; cellX < cellCols; cellX++)
        {
            int idx = cellIndex + cellX + cellY * m_cellNumX;
            if (idx >= 0 && idx < (int)m_cells.size())
            {
                ObjectSharedPtrs& objs = m_cells[idx];
                for (auto i = objs.begin(); i != objs.end(); ++i)
                {
                    (*i)->draw(c, r);
                }
            }
        }
    }
}

bool Simulator::isColliding(Object* collidee, int x, int y, int& z)
{
    bool colliding = false;

    int worldZ = m_world->getHeightAt(x, y, z);
    colliding = Math::abs(worldZ - z) > MAX_STEP;
    z = worldZ;

    if (!colliding)
    {
        int cellIndex = getCellIndex(x, y);
        assert(cellIndex < (int)m_cells.size());
        assert(cellIndex >= 0);
        ObjectSharedPtrs& cell = m_cells[cellIndex];

        for (auto j = cell.begin(); j != cell.end(); ++j)
        {
            Object* collider = (*j).get();

            if (collidee == collider)
            {
                continue;
            }

            if (collider->isCollidable() &&
                collider->getX() == x &&
                collider->getY() == y &&
                Math::abs(collider->getZ() - z) < MAX_STEP)
            {
                colliding = true;
                break;
            }
        }
    }

    return colliding;
}

bool Simulator::listObjectsAt(int x, int y, int /*z*/, ObjectWeakPtrs* result)
{
    if (!result)
    {
        return false;
    }

    int cellIndex = getCellIndex(x, y);
    assert(cellIndex < (int)m_cells.size());
    assert(cellIndex >= 0);
    ObjectSharedPtrs& cell = m_cells[cellIndex];

    std::for_each(
        cell.begin(), cell.end(), [result, x, y] (const ObjectSharedPtr& obj)
        {
            if (obj->getX() == x && obj->getY() == y)
            {
                result->push_back(obj);
            }
        });

    return !result->empty();
}

bool Simulator::findObjectsAround(int x, int y, int /*z*/, float radius, ObjectWeakPtrs* result)
{
    if (!result)
    {
        return false;
    }

    int iradius   = (int)radius;
    int sqrRadius = iradius * iradius;
    int cellIndex = getCellIndex(x - iradius, y - iradius);
    int cells     = iradius / m_cellSize + 1;
    int cellCount = (int)m_cells.size();

    for (int cellY = 0; cellY < cells; cellY++)
    {
        for (int cellX = 0; cellX < cells; cellX++)
        {
            int idx = cellIndex + cellX + cellY * m_cellNumX;
            if (idx >= 0 && idx < cellCount)
            {
                ObjectSharedPtrs& cells = m_cells[idx];
                std::for_each(
                    cells.begin(), cells.end(),
                    [result, x, y, sqrRadius] (const ObjectSharedPtr& obj)
                    {
                        if (Math::sqrDistance(x, y, obj->getX(), obj->getY()) <= sqrRadius)
                        {
                            result->push_back(obj);
                        }
                    });
            }
        }
    }

    return !result->empty();
}

void Simulator::initCell()
{
    if (!m_world)
    {
        m_cellNumX = 0;
        m_cellNumY = 0;
        m_cells.clear();
        return;
    }

    m_cellNumX = m_world->getWidth() / m_cellSize + 1;
    m_cellNumY = m_world->getHeight() / m_cellSize + 1;

    int numCell = m_cellNumX * m_cellNumY;
    m_cells.resize(numCell);
    std::for_each(
        m_cells.begin(), m_cells.end(), [] (ObjectSharedPtrs& objs)
        {
            objs.reserve(10);
        });
}

int Simulator::getCellIndex(int x, int y)
{
    return x / m_cellSize + y / m_cellSize * m_cellNumX;
}
