#pragma once

#include "cobject.h"
#include "cworld.h"
#include <vector>

class Renderer;

class Simulator
{
public:

    static Simulator* get();

    void setWorld(const WorldPtr& world);

    void add(const ObjectPtr& object);

    void spawn(const ObjectPtr& object);

    void remove(const ObjectPtr& object);

    void activate(Object* object);

    void tick(float dt);

    void draw(Renderer* r);

    bool isColliding(Object* collidee, float x, float y, float z, float& ground);

private:

    typedef std::vector<ObjectPtr> Objects;
    WorldPtr m_world;
    Objects m_objects;
    Objects m_objectsToRemove;
    std::vector<Object*> m_activated;
};
