#pragma once

#include "cobject.h"
#include "cworld.h"
#include <vector>

class Renderer;
class Character;

class Simulator
{
public:

    static Simulator* get();

    void setWorld(const WorldPtr& world);

    void add(const ObjectPtr& object);

    void spawn(const ObjectPtr& object);

    void remove(Object* object);

    void activate(Object* object);

    void tick(float dt);

    void draw(Renderer* r);

    bool isColliding(Object* collidee, float x, float y, float z, float& ground);

    bool findTarget(float x, float y, float z, Object** target);

private:

    typedef std::vector<ObjectPtr> ObjectPtrs;
    typedef std::vector<Object*> Objects;
    WorldPtr m_world;
    ObjectPtrs m_objects;
    Objects m_objectsToRemove;
    Objects m_activated;
};
