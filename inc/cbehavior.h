#pragma once

class Character;

class Behavior
{
public:
    virtual ~Behavior() {}

    virtual const char* getName() const = 0;

    virtual void tick(float dt, Character* object) = 0;

};

class BehaviorWander : public Behavior
{
public:
    BehaviorWander();

    virtual const char* getName() const override;

    virtual void tick(float dt, Character* object) override;

private:
    bool m_initialized;
    float m_anchorX;
    float m_anchorY;
    float m_ropeLength;
    float m_moveTime;
};


class BehaviorAttack : public Behavior
{
public:
    BehaviorAttack();

    virtual const char* getName() const override;

    virtual void tick(float dt, Character* object) override;

};
