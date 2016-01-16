#include "csimulator.h"
#include "cmath.h"
#include "crenderer.h"

#include <stdio.h>
#include <float.h>

static const int MAX_STEP = 2;

Simulator* Simulator::get()
{
    static Simulator instance;
    return &instance;
}

void Simulator::setWorld(const WorldSharedPtr& world)
{
    m_world = world;
}

void Simulator::add(const ObjectSharedPtr& object)
{
    m_objects.push_back(object);
}

void Simulator::spawn(const ObjectSharedPtr& object)
{
    while (true)
    {
        int x = Math::ceilRandom(m_world->getWidth());
        int y = Math::ceilRandom(m_world->getHeight());
        int z = INT_MAX;
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
    for (auto i = m_objects.begin(); i != m_objects.end(); ++i)
    {
        const ObjectSharedPtr& obj = *i;
        obj->tick(dt);
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
            collidee->setPosition(newX, newY, newZ);
        }

        collidee->stop();
    }

    m_activated.clear();

    for (auto i = m_removed.begin(); i != m_removed.end(); ++i)
    {
        Object* obj = *i;
        auto it = std::find_if(
            m_objects.begin(), m_objects.end(),
            [obj](const ObjectSharedPtr& other)
            {
                return other.get() == obj;
            });

        if (it != m_objects.end())
        {
            m_objects.erase(it);
        }
    }
}

void Simulator::draw(Renderer* r)
{
    m_world->draw(r);
    for (auto i = m_objects.begin(); i != m_objects.end(); ++i)
    {
        (*i)->draw(r);
    }
}

bool Simulator::isColliding(Object* collidee, int x, int y, int& z)
{
    bool colliding(false);

    int worldZ = 0; //m_world->getHeightAt(x, y);
    if (worldZ - z > MAX_STEP)
    {
        colliding = true;
    }

    z = worldZ+1;

    for (auto j = m_objects.begin(); !colliding && j != m_objects.end(); ++j)
    {
        Object* collider = (*j).get();

        if (collidee == collider)
        {
            continue;
        }

        if (collider->getX() == x &&
            collider->getY() == y &&
            Math::abs(collider->getZ() - z) < MAX_STEP)
        {
            colliding = true;
            break;
        }
    }

    return colliding;
}

bool Simulator::findObjectAt(int x, int y, int z, Object** result)
{
    for (auto j = m_objects.begin(); j != m_objects.end(); ++j)
    {
        Object* obj = (*j).get();

        if (obj->getX() == x &&
            obj->getY() == y)
        {
            if (result)
            {
                *result = obj;
            }
            return true;
        }
    }
    return false;
}

void Simulator::findObjectsAround(int x, int y, int z, float radius, ObjectWeakPtrs* result)
{
    if (!result)
    {
        return;
    }

    float sqrRadius = radius * radius;
    for (auto j = m_objects.begin(); j != m_objects.end(); ++j)
    {
        ObjectSharedPtr& obj = *j;

        if (Math::sqrDistance(x, y, obj->getX(), obj->getY()) <= sqrRadius)
        {
            result->push_back(obj);
        }
    }
}
