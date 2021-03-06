#include "cbehavior.h"
#include "ccharacter.h"
#include "csimulator.h"
#include "cmath.h"
#include "cfaction.h"
#include "clogger.h"
#include "cdebugger.h"

////////////////////////////////////////////////////////////////////////////////
// mistke this hello
void Blackboard::setSelf(Character* self)
{
    m_self = self;
}

Character* Blackboard::getSelf() const
{
    return m_self;
}

void Blackboard::setReference(BlackboardReference ref, const ObjectWeakPtr& obj)
{
    m_references.insert(References::value_type(ref, obj));
}

void Blackboard::clearReference(BlackboardReference ref)
{
    m_references.erase(ref);
}

ObjectWeakPtr Blackboard::getReference(BlackboardReference ref) const
{
    auto it = m_references.find(ref);
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

void BehaviorReferenceNode::setReference(BlackboardReference ref)
{
    m_reference = ref;
}

BlackboardReference BehaviorReferenceNode::getReference() const
{
    return m_reference;
}

////////////////////////////////////////////////////////////////////////////////

BehaviorFindTarget::BehaviorFindTarget()
    : m_distance(0)
    , m_hysteresis(0)
    , m_remain(0)
{

}

void BehaviorFindTarget::setVisionRadius(float dist, float hysteresis)
{
    m_distance = dist;
    m_hysteresis = hysteresis;
}

void BehaviorFindTarget::tick(float dt, Blackboard& bb)
{
    CDEBUG_HIGH(ObjectWeakPtr ref = bb.getReference(getReference());
           if (!ref.expired())
           {
               ObjectSharedPtr target = ref.lock();
               std::wstringstream s;
               s << CHAR_T(":") << ((Character*)target.get())->getName();
               bb.getSelf()->debugStringAppend(s.str());
           }
           else
           {
               bb.getSelf()->debugStringAppend(CHAR_T(":"));
           }
        );

    m_remain -= dt;
    if (m_remain < 0)
    {
        m_remain = Math::intervalRandom(0.4f, 0.6f);

        int x = bb.getSelf()->getX();
        int y = bb.getSelf()->getY();
        int z = bb.getSelf()->getZ();

        ObjectWeakPtr ref = bb.getReference(getReference());
        if (!ref.expired())
        {
            ObjectSharedPtr target = ref.lock();
            Character* c = (Character*)target.get();
            float dist = Math::sqrDistance(
                target->getX(), target->getY(), x, y);

            if (c->getHp() && dist < m_distance + m_hysteresis)
            {
                return;
            }
            CLOG_DEBUG("lost sight of target:" << c->getName());
            bb.clearReference(getReference());
        }

        ObjectWeakPtrs objects;
        Simulator::get().findObjectsAround(
            x, y, z, m_distance, &objects);

        std::find_if(
            objects.begin(), objects.end(),
            [this, &bb] (const ObjectWeakPtr& o)
            {
                const ObjectSharedPtr& obj = o.lock();
                if (obj &&
                    obj.get() != bb.getSelf() &&
                    obj->getObjectType() & Object::OBJECT_TYPE_CHARACTER)
                {
                    Character* c = (Character*)obj.get();
                    if (c->getHp() &&
                        bb.getSelf()->getFaction()->isEnemy(c->getFaction()))
                    {
                        CLOG_DEBUG("found target:" << c->getName());
                        bb.setReference(getReference(), obj);
                        return true;
                    }
                }
                return false;
            });
    }
}

////////////////////////////////////////////////////////////////////////////////

BehaviorReferencePredicate::BehaviorReferencePredicate()
    : m_reference(BlackboardReference::NONE)
{

}

void BehaviorReferencePredicate::setReference(BlackboardReference ref)
{
    m_reference = ref;
}

BlackboardReference BehaviorReferencePredicate::getReference() const
{
    return m_reference;
}


bool BehaviorReferencePredicate::eval(Blackboard& bb)
{
    return !bb.getReference(m_reference).expired();
}

////////////////////////////////////////////////////////////////////////////////

BehaviorDistancePredicate::BehaviorDistancePredicate()
    : m_sqrDistance(0)
    , m_hysteresis(0)
    , m_greaterThan(false)
    , m_last(false)
{

}

void BehaviorDistancePredicate::setSqrDistance(int sqrDistance)
{
    m_sqrDistance = sqrDistance;
}

void BehaviorDistancePredicate::setHysteresis(int hysteresis)
{
    m_hysteresis = hysteresis;
}


void BehaviorDistancePredicate::setGreaterThan(bool value)
{
    m_greaterThan = value;
}

bool BehaviorDistancePredicate::eval(Blackboard& bb)
{
    ObjectWeakPtr ref = bb.getReference(getReference());
    if (ref.expired())
    {
        return false;
    }

    ObjectSharedPtr obj = ref.lock();

    int dist = Math::sqrDistance(
        obj->getX(),
        obj->getY(),
        bb.getSelf()->getX(),
        bb.getSelf()->getY());

    bool answer;
    if (m_greaterThan)
    {
        answer = m_last ? dist >= m_sqrDistance - m_hysteresis : dist >= m_sqrDistance;
    }
    else
    {
        answer = m_last ? dist <= m_sqrDistance + m_hysteresis : dist <= m_sqrDistance;
    }

    if (answer != m_last)
    {
        CLOG_DEBUG("distance predicate change to " << (answer ? "true" : "false") << " for target " << ((Character*)obj.get())->getName());
        m_last = answer;
    }

    return m_last;
}

////////////////////////////////////////////////////////////////////////////////

BehaviorAlternative::BehaviorAlternative()
    : m_remain(0)
    , m_predicate(nullptr)
    , m_current(nullptr)
    , m_true(nullptr)
    , m_false(nullptr)
{

}

BehaviorAlternative::~BehaviorAlternative()
{
    setTrue(nullptr);
    setFalse(nullptr);
    setPredicate(nullptr);
}

void BehaviorAlternative::setTrue(BehaviorNode* node)
{
    delete m_true;
    m_true = node;
}

void BehaviorAlternative::setFalse(BehaviorNode* node)
{
    delete m_false;
    m_false = node;
}

void BehaviorAlternative::setPredicate(BehaviorPredicate* predicate)
{
    delete m_predicate;
    m_predicate = predicate;
}

void BehaviorAlternative::tick(float dt, Blackboard& bb)
{
    m_remain -= dt;
    if (!m_current || m_remain < 0)
    {
        m_remain = Math::intervalRandom(0.4f, 0.6f);
        BehaviorNode* node = m_predicate->eval(bb) ? m_true : m_false;
        if (node != m_current)
        {
            CLOG_DEBUG("changing behavior from " << (m_current ? m_current->getName() : "null") << " to " << node->getName());
            m_current = node;
        }
    }
    m_current->tick(dt, bb);
}

////////////////////////////////////////////////////////////////////////////////

BehaviorWander::BehaviorWander()
    : m_initialized(false)
    , m_anchorX(0)
    , m_anchorY(0)
    , m_dx(0)
    , m_dy(0)
    , m_ropeSqrLength(5)
    , m_remain(0)
{

}

void BehaviorWander::setRopeSqrLength(int sqrLength)
{
    m_ropeSqrLength = sqrLength;
}

void BehaviorWander::tick(float dt, Blackboard& bb)
{
    CDEBUG_HIGH(bb.getSelf()->debugStringAppend(CHAR_T("w")));

    if (!m_initialized)
    {
        m_initialized = true;
        m_anchorX = bb.getSelf()->getX();
        m_anchorY = bb.getSelf()->getY();
    }

    m_remain -= dt;
    if (m_remain >= 0)
    {
        return;
    }

    m_remain = Math::intervalRandom(0.4f, 0.6f);

    // do we change what we where doing?
    if (Math::ceilRandom(100) < 20)
    {
        bool stop = Math::ceilRandom(100) < 20;
        if (stop && (m_dx || m_dy))
        {
            m_dx = 0;
            m_dy = 0;
        }
        else if (!m_dx && !m_dy)
        {
            bool turn = Math::ceilRandom(100) < 20;
            int val = Math::ceilRandom(2) * 2 - 1;
            m_dx = turn ? val : 0;
            m_dy = turn ? 0 : val;
        }
        else
        {
            bool back = Math::ceilRandom(100) < 10;
            if (back)
            {
                m_dx *= -1;
                m_dy *= -1;
            }
            else
            {
                bool turn = Math::ceilRandom(100) < 20;
                if (turn)
                {
                    bool right = Math::ceilRandom(100) < 50;
                    if (m_dx)
                    {
                        m_dy = right ? m_dx : -m_dx;
                        m_dx = 0;
                    }
                    else if (m_dy)
                    {
                        m_dx = right ? -m_dy : m_dy;
                        m_dy = 0;
                    }
                }
            }
        }
    }

    int newX = m_dx + bb.getSelf()->getX();
    int newY = m_dy + bb.getSelf()->getY();
    if (Math::sqrDistance(newX, newY, m_anchorX, m_anchorY) < m_ropeSqrLength)
    {
        bb.getSelf()->setDisplacement(m_dx, m_dy);
    }
    else
    {
        m_dx = 0;
        m_dy = 0;
    }
}

//////////////////////////////////////////////////////////////////////

BehaviorChase::BehaviorChase()
    : m_remain(0)
{

}

void BehaviorChase::tick(float dt, Blackboard& bb)
{
    CDEBUG_HIGH(bb.getSelf()->debugStringAppend(CHAR_T("c")));

    m_remain -= dt;
    if (m_remain >= 0)
    {
        return;
    }

    m_remain = Math::intervalRandom(0.3f, 0.4f);

    ObjectWeakPtr ref = bb.getReference(getReference());
    if (ref.expired())
    {
        return;
    }

    ObjectSharedPtr obj = ref.lock();
    int dx = obj->getX() - bb.getSelf()->getX();
    int dy = obj->getY() - bb.getSelf()->getY();
    int absDx = Math::abs(dx);
    int absDy = Math::abs(dy);

    if (absDx > absDy)
    {
        bb.getSelf()->setDisplacement(dx / absDx, 0);
    }
    else if (absDy != 0)
    {
        bb.getSelf()->setDisplacement(0, dy / absDy);
    }
}

//////////////////////////////////////////////////////////////////////

BehaviorAttack::BehaviorAttack()
    : m_remain(0)
{

}

void BehaviorAttack::tick(float dt, Blackboard& bb)
{
    CDEBUG_HIGH(bb.getSelf()->debugStringAppend(CHAR_T("a")));

    m_remain -= dt;
    if (m_remain >= 0)
    {
        return;
    }

    ObjectWeakPtr ref = bb.getReference(getReference());
    if (ref.expired())
    {
        return;
    }

    ObjectSharedPtr obj = ref.lock();
    if (!(obj->getObjectType() & Object::OBJECT_TYPE_CHARACTER))
    {
        return;
    }

    auto c = (Character*)obj.get();
    if (c->getHp() <= 0)
    {
        return;
    }

    int dx = obj->getX() - bb.getSelf()->getX();
    int dy = obj->getY() - bb.getSelf()->getY();

    if (dx > 0)
    {
        bb.getSelf()->hit(Direction::RIGHT);
    }
    else if (dx < 0)
    {
        bb.getSelf()->hit(Direction::LEFT);
    }
    else if (dy > 0)
    {
        bb.getSelf()->hit(Direction::DOWN);
    }
    else
    {
        bb.getSelf()->hit(Direction::UP);
    }
    m_remain = Math::intervalRandom(0.4f, 0.6f);
}
