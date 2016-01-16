#pragma once

#include "cobject.h"

#include <string>
#include <vector>
#include <map>


class Character;

class Blackboard
{
public:

    void setSelf(Character* self);

    Character* getSelf() const;

    void setReference(const std::string& name, const ObjectWeakPtr& obj) const;

    ObjectWeakPtr getReference(const std::string& name) const;

private:
    Character* m_self;
    typedef std::map<std::string, ObjectWeakPtr> References;
    References m_references;
};

////////////////////////////////////////////////////////////////////////////////

class BehaviorNode
{
public:
    virtual ~BehaviorNode() {}

    virtual void tick(float dt, Blackboard& bb) = 0;

};

typedef std::vector<BehaviorNode*> BehaviorNodes;

////////////////////////////////////////////////////////////////////////////////

class BehaviorComposite : public BehaviorNode
{
public:
    virtual ~BehaviorComposite();

    void add(BehaviorNode* node);

    virtual void tick(float dt, Blackboard& bb) override;

private:
    BehaviorNodes m_nodes;
};

////////////////////////////////////////////////////////////////////////////////

class BehaviorFindTarget : public BehaviorNode
{
public:

    void setVisionSqrRadius(float dist, float hysteresis);

    virtual void tick(float dt, Blackboard& bb) = 0;

private:
    float m_distance;
    float m_hysteresis;
};

////////////////////////////////////////////////////////////////////////////////

class BehaviorWander : public BehaviorNode
{
public:
    BehaviorWander();

    virtual void tick(float dt, Blackboard& bb) override;

private:
    bool m_initialized;
    int m_anchorX;
    int m_anchorY;
    int m_ropeLength;
    float m_moveTime;
};

class BehaviorChase : public BehaviorNode
{
public:

    virtual void tick(float dt, Blackboard& bb) override;

};

class BehaviorAttack : public BehaviorNode
{
public:

    virtual void tick(float dt, Blackboard& bb) override;

};
