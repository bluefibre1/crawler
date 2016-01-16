#include "cbehavior.h"
#include "ccharacter.h"
#include "csimulator.h"
#include "cmath.h"

#include <stdio.h>


////////////////////////////////////////////////////////////////////////////////

void Blackboard::setSelf(Character* self)
{
    m_self = self;
}

Character* Blackboard::getSelf() const
{
    return m_self;
}

void Blackboard::setReference(const std::string& name, const ObjectWeakPtr& obj)
{
    m_references.insert(References::value_type(name, obj));
}

void Blackboard::clearReference(const std::string& name)
{
    m_references.erase(name);
}

ObjectWeakPtr Blackboard::getReference(const std::string& name) const
{
    auto it = m_references.find(name);
    if (it != m_references.end())
    {
        return (*it).second;
    }
    return ObjectWeakPtr();
}

////////////////////////////////////////////////////////////////////////////////

BehaviorComposite::~BehaviorComposite()
{
    for (auto i = m_nodes.begin(); i != m_nodes.end(); ++i)
    {
        delete *i;
    }
}

void BehaviorComposite::add(BehaviorNode* node)
{
    m_nodes.push_back(node);
}

void BehaviorComposite::tick(float dt, Blackboard& bb)
{
    for (auto i = m_nodes.begin(); i != m_nodes.end(); ++i)
    {
        (*i)->tick(dt, bb);
    }
}

////////////////////////////////////////////////////////////////////////////////

std::string BehaviorFindTarget::m_referenceName = "target";

BehaviorFindTarget::BehaviorFindTarget()
    : m_distance(0)
    , m_hysteresis(0)
    , m_elapsed(0)
{

}

void BehaviorFindTarget::setVisionSqrRadius(float dist, float hysteresis)
{
    m_distance = dist;
    m_hysteresis = dist;
}

void BehaviorFindTarget::tick(float dt, Blackboard& bb)
{
    m_elapsed += dt;
    if (m_elapsed > 0.5f)
    {
        m_elapsed = 0;

        int x = bb.getSelf()->getX();
        int y = bb.getSelf()->getY();
        int z = bb.getSelf()->getZ();

        ObjectWeakPtr ref = bb.getReference(m_referenceName);
        if (!ref.expired())
        {
            ObjectSharedPtr target = ref.lock();
            float dist = Math::sqrDistance(
                target->getX(), target->getY(), x, y);

            if (dist < m_distance + m_hysteresis)
            {
                return;
            }
            bb.clearReference(m_referenceName);
        }

        ObjectWeakPtrs objects;
        Simulator::get()->findObjectsAround(
            x, y, z, m_distance, &objects);

        for (auto i = objects.begin(); i != objects.end(); ++i)
        {
            ObjectSharedPtr obj = (*i).lock();
            if (!obj || !obj->isCharacter())
            {
                continue;
            }

            Character* c = (Character*)obj.get();
            if (bb.getSelf()->getFaction()->isEnemy(c->getFaction()))
            {
                bb.setReference(m_referenceName, obj);
                break;
            }
        }

    }
}

////////////////////////////////////////////////////////////////////////////////
/*
BehaviorWander::BehaviorWander()
    : m_initialized(false)
    , m_anchorX(0)
    , m_anchorY(0)
    , m_ropeLength(10)
    , m_moveTime(0)
{

}

const char* BehaviorWander::getName() const
{
    return "Wander";
}

void BehaviorWander::tick(float dt, Character* object)
{
    if (!m_initialized)
    {
        m_initialized = true;
        m_anchorX = object->getX();
        m_anchorY = object->getY();
    }

    m_moveTime += dt;
    if (m_moveTime < 0.5f)
    {
        return;
    }

    m_moveTime = 0;

    // do we move?
    if (Math::wrapRandom() > 0)
    {
        return;
    }

    // which direction?
    if (Math::wrapRandom() > 0)
    {
        // left - right
        if (Math::wrapRandom() > 0)
        {
            object->setDisplacement(1, 0);
        }
        else
        {
            object->setDisplacement(-1, 0);
        }
    }
    else
    {
        // up - down
        if (Math::wrapRandom() > 0)
        {
            object->setDisplacement(0, 1);
        }
        else
        {
            object->setDisplacement(0, -1);
        }
    }

    int newX = object->getDisplacementX() + object->getX();
    int newY = object->getDisplacementY() + object->getY();

    if (Math::distance(newX, newY, m_anchorX, m_anchorY) > m_ropeLength)
    {
        object->stop();
    }
}

//////////////////////////////////////////////////////////////////////

BehaviorChase::BehaviorChase()
{

}

const char* BehaviorChase::getName() const
{
    return "Attack";
}

void BehaviorChase::tick(float dt, Character* object)
{

}

//////////////////////////////////////////////////////////////////////

BehaviorAttack::BehaviorAttack()
{

}

const char* BehaviorAttack::getName() const
{
    return "Attack";
}

void BehaviorAttack::tick(float dt, Character* object)
{

}
*/
