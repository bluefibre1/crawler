#pragma once

#include "cobject.h"

#include <string>
#include <vector>
#include <map>


class Character;

enum class BlackboardReference
{
    NONE,
    TARGET,
};

class Blackboard
{
public:

    void setSelf(Character* self);

    Character* getSelf() const;

    void setReference(BlackboardReference ref, const ObjectWeakPtr& obj);

    void clearReference(BlackboardReference ref);

    ObjectWeakPtr getReference(BlackboardReference ref) const;

private:
    Character* m_self;
    typedef std::map<BlackboardReference, ObjectWeakPtr> References;
    References m_references;
};

////////////////////////////////////////////////////////////////////////////////

class BehaviorNode
{
public:
    virtual ~BehaviorNode() {}

    virtual void tick(float dt, Blackboard& bb) = 0;

};

////////////////////////////////////////////////////////////////////////////////

typedef std::vector<BehaviorNode*> BehaviorNodePtrs;

class BehaviorComposite : public BehaviorNode
{
public:
    virtual ~BehaviorComposite();

    void add(BehaviorNode* node);

    virtual void tick(float dt, Blackboard& bb) override;

private:
    BehaviorNodePtrs m_nodes;
};

////////////////////////////////////////////////////////////////////////////////

class BehaviorReferenceNode : public BehaviorNode
{
public:

    void setReference(BlackboardReference ref);

    BlackboardReference getReference() const;

private:
    BlackboardReference m_reference;
};

////////////////////////////////////////////////////////////////////////////////

class BehaviorFindTarget : public BehaviorReferenceNode
{
public:
    BehaviorFindTarget();

    void setVisionSqrRadius(float dist, float hysteresis);

    virtual void tick(float dt, Blackboard& bb) override;

private:
    float m_distance;
    float m_hysteresis;
    float m_elapsed;
};

////////////////////////////////////////////////////////////////////////////////

class BehaviorPredicate
{
public:

    virtual ~BehaviorPredicate() {}

    virtual bool eval(Blackboard& bb) = 0;
};

////////////////////////////////////////////////////////////////////////////////

class BehaviorReferencePredicate : public BehaviorPredicate
{
public:
    BehaviorReferencePredicate();

    void setReference(BlackboardReference ref);

    BlackboardReference getReference() const;

    virtual bool eval(Blackboard& bb) override;

private:
    BlackboardReference m_reference;
};

////////////////////////////////////////////////////////////////////////////////

class BehaviorDistancePredicate : public BehaviorReferencePredicate
{
public:
    BehaviorDistancePredicate();

    void setSqrDistance(float sqrDistance);

    void setHysteresis(float hysteresis);

    void setGreaterThan(bool value);

    virtual bool eval(Blackboard& bb) override;

private:
    float m_sqrDistance;
    float m_hysteresis;
    bool m_greaterThan;
    bool m_last;
};

////////////////////////////////////////////////////////////////////////////////

class BehaviorAlternative : public BehaviorNode
{
public:
    BehaviorAlternative();
    virtual ~BehaviorAlternative();

    void setTrue(BehaviorNode* node);

    void setFalse(BehaviorNode* node);

    void setPredicate(BehaviorPredicate* pred);

    virtual void tick(float dt, Blackboard& bb) override;

private:
    float m_elapsed;
    BehaviorPredicate* m_predicate;
    BehaviorNode* m_current;
    BehaviorNode* m_true;
    BehaviorNode* m_false;
};

////////////////////////////////////////////////////////////////////////////////

class BehaviorWander : public BehaviorNode
{
public:
    BehaviorWander();

    void setRopeSqrLength(int sqrLength);

    virtual void tick(float dt, Blackboard& bb) override;

private:
    bool m_initialized;
    int m_anchorX;
    int m_anchorY;
    int m_dx;
    int m_dy;
    int m_ropeSqrLength;
    float m_elapsed;
};

////////////////////////////////////////////////////////////////////////////////

class BehaviorChase : public BehaviorReferenceNode
{
public:
    BehaviorChase();

    virtual void tick(float dt, Blackboard& bb) override;

private:
    float m_elapsed;
};

////////////////////////////////////////////////////////////////////////////////

class BehaviorAttack : public BehaviorReferenceNode
{
public:
    BehaviorAttack();

    virtual void tick(float dt, Blackboard& bb) override;

private:
    float m_elapsed;
};
