#include "csimulator.h"
#include "cmath.h"
#include "crenderer.h"

#include <stdio.h>
#include <float.h>

static const int MAX_STEP = 10000;

Simulator* Simulator::get()
{
    static Simulator instance;
    return &instance;
}

void Simulator::setWorld(const WorldPtr& world)
{
    m_world = world;
}

void Simulator::add(const ObjectPtr& object)
{
    m_objects.push_back(object);
}

void Simulator::spawn(const ObjectPtr& object)
{
    while (true)
    {
        int x = Math::ceilRandom(m_world->getWidth());
        int y = Math::ceilRandom(m_world->getHeight());
        float z = FLT_MAX;
        if (!isColliding(object.get(), x, y, z, z))
        {
            object->setPosition(x,y,z);
            break;
        }
    }

    add(object);
}

void Simulator::remove(Object* object)
{
    m_objectsToRemove.push_back(object);
}

void Simulator::activate(Object* object)
{
    m_activated.push_back(object);
}

void Simulator::tick(float dt)
{
    for (auto i = m_objects.begin(); i != m_objects.end(); ++i)
    {
        const ObjectPtr& obj = *i;
        obj->tick(dt);
    }

    for (auto i = m_activated.begin(); i != m_activated.end(); ++i)
    {
        Object* collidee = *i;

        float newX = collidee->getX() + collidee->getVelocityX() * dt;
        float newY = collidee->getY() + collidee->getVelocityY() * dt;
        float newZ = collidee->getZ() + collidee->getVelocityZ() * dt;

        Math::clamp(newX, 0, m_world->getWidth() - 1);
        Math::clamp(newY, 0, m_world->getHeight() - 1);

        if (isColliding(collidee, newX, newY, newZ, newZ))
        {
            collidee->setVelocity(0, 0, 0);
        }
        else
        {
            collidee->setPosition(newX, newY, newZ);
            if (collidee->getFriction() > 0)
            {
                collidee->setVelocity(0, 0, 0);
            }
        }
    }

    m_activated.clear();

    for (auto i = m_objectsToRemove.begin(); i != m_objectsToRemove.end(); ++i)
    {
        Object* obj = *i;
        auto it = std::find_if(
            m_objects.begin(), m_objects.end(),
            [obj](const ObjectPtr& other)
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

bool Simulator::isColliding(Object* collidee, float x, float y, float z, float& ground)
{
    bool colliding(false);

    float worldZ = m_world->getHeightAt(x, y);
    if (worldZ - z > MAX_STEP)
    {
        colliding = true;
    }

    ground = worldZ;

    for (auto j = m_objects.begin(); !colliding && j != m_objects.end(); ++j)
    {
        Object* collider = (*j).get();

        if (collidee == collider)
        {
            continue;
        }

        if (Math::isEqual(collider->getX(), x, 0.5f) &&
            Math::isEqual(collider->getY(), y, 0.5f) &&
            Math::isEqual(collider->getZ(), z, 0.5f))
        {
            colliding = true;
            break;
        }
    }

    return colliding;
}

bool Simulator::findTarget(float x, float y, float z, Object** target)
{
    for (auto j = m_objects.begin(); j != m_objects.end(); ++j)
    {
        Object* collider = (*j).get();

        if (collider->getX() == x &&
            collider->getY() == y)
        {
            if (target)
            {
                *target = collider;
            }
            return true;
        }
    }
    return false;
}
