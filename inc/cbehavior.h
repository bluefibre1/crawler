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

    virtual const char* getName() const = 0;

    virtual void tick(float dt, Blackboard& bb) = 0;

};

////////////////////////////////////////////////////////////////////////////////

typedef std::vector<BehaviorNode*> BehaviorNodePtrs;

class BehaviorComposite : public BehaviorNode
{
public:
    virtual ~BehaviorComposite();

    virtual const char* getName() const override { return "composite"; }

    void add(BehaviorNode* node);

    virtual void tick(float dt, Blackboard& bb) override;

private:
    BehaviorNodePtrs m_nodes;
};

////////////////////////////////////////////////////////////////////////////////

class BehaviorReferenceNode : public BehaviorNode
{
public:

    virtual const char* getName() const override { return "reference"; }

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

    virtual const char* getName() const override { return "find target"; }

    void setVisionRadius(float dist, float hysteresis);

    virtual void tick(float dt, Blackboard& bb) override;

private:
    float m_distance;
    float m_hysteresis;
    float m_remain;
};

////////////////////////////////////////////////////////////////////////////////

class BehaviorPredicate
{
public:

    virtual ~BehaviorPredicate() {}

    virtual const char* getName() const { return "predicate"; }

    virtual bool eval(Blackboard& bb) = 0;
};

////////////////////////////////////////////////////////////////////////////////

class BehaviorReferencePredicate : public BehaviorPredicate
{
public:
    BehaviorReferencePredicate();

    virtual const char* getName() const override { return "reference predicate"; }

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

    virtual const char* getName() const override { return "distance predicate"; }

    void setSqrDistance(int sqrDistance);

    void setHysteresis(int hysteresis);

    void setGreaterThan(bool value);

    virtual bool eval(Blackboard& bb) override;

private:
    int m_sqrDistance;
    int m_hysteresis;
    bool m_greaterThan;
    bool m_last;
};

////////////////////////////////////////////////////////////////////////////////

class BehaviorAlternative : public BehaviorNode
{
public:
    BehaviorAlternative();
    virtual ~BehaviorAlternative();

    virtual const char* getName() const override { return "alternative"; }

    void setTrue(BehaviorNode* node);

    void setFalse(BehaviorNode* node);

    void setPredicate(BehaviorPredicate* pred);

    virtual void tick(float dt, Blackboard& bb) override;

private:
    float m_remain;
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

    virtual const char* getName() const override { return "wander"; }

    void setRopeSqrLength(int sqrLength);

    virtual void tick(float dt, Blackboard& bb) override;

private:
    bool m_initialized;
    int m_anchorX;
    int m_anchorY;
    int m_dx;
    int m_dy;
    int m_ropeSqrLength;
    float m_remain;
};

////////////////////////////////////////////////////////////////////////////////

class BehaviorChase : public BehaviorReferenceNode
{
public:
    BehaviorChase();

    virtual const char* getName() const override { return "chase"; }

    virtual void tick(float dt, Blackboard& bb) override;

private:
    float m_remain;
};

////////////////////////////////////////////////////////////////////////////////

class BehaviorAttack : public BehaviorReferenceNode
{
public:
    BehaviorAttack();

    virtual const char* getName() const override { return "attack"; }

    virtual void tick(float dt, Blackboard& bb) override;

private:
    float m_remain;
};
