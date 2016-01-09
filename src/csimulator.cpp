#include "csimulator.h"
#include "cmath.h"

#include "stdio.h"

static const int MAX_STEP = 10;

Simulator* Simulator::get()
{
    static Simulator instance;
    return &instance;
}

void Simulator::setWorld(World* world)
{
    m_world = world;
}

void Simulator::addCollider(Object* object)
{
    m_colliders.push_back(object);
}

void Simulator::removeCollider(Object* object)
{
    m_collidersToRemove.push_back(object);
}

void Simulator::activate(Object* object)
{
    m_objects.push_back(object);
}

void Simulator::tick(float dt)
{
    for (auto i = m_objects.begin(); i != m_objects.end(); ++i)
    {
        Object* collidee = *i;

        float newX = collidee->getX() + collidee->getVelocityX() * dt;
        float newY = collidee->getY() + collidee->getVelocityY() * dt;
        float newZ = collidee->getZ() + collidee->getVelocityZ() * dt;

        Math::clamp(newX, 0, m_world->getWidth()-1);
        Math::clamp(newY, 0, m_world->getHeight()-1);

        bool colliding = false;
        float worldZ = m_world->getHeightAt(newX, newY);
        if (worldZ - newZ > MAX_STEP)
        {
            colliding = true;
        }
        else
        {
            // snap to ground
            newZ = worldZ;
        }

        for (auto j = m_colliders.begin(); !colliding && j != m_colliders.end(); ++j)
        {
            Object* collider = *j;

            if (collidee == collider)
            {
                continue;
            }

            if (collider->getX() == newX &&
                collider->getY() == newY &&
                collider->getZ() == newZ)
            {
                colliding = true;
                break;
            }
        }

        if (colliding)
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

    m_objects.clear();

    for (auto i = m_collidersToRemove.begin(); i != m_collidersToRemove.end(); ++i)
    {
        Object* collider = *i;
        auto it = std::find(m_colliders.begin(), m_colliders.end(), collider);
        if (it != m_colliders.end())
        {
            m_colliders.erase(it);
        }
    }
}
