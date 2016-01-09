#pragma once

#include "cobject.h"
#include "cworld.h"
#include <vector>

class Renderer;

class Simulator
{
public:

    static Simulator* get();

    void setWorld(World* world);

    void add(Object* object);

    void spawn(Object* object);

    void remove(Object* object);

    void activate(Object* object);

    void tick(float dt);

    void draw(Renderer* r);

    bool isColliding(Object* collidee, float x, float y, float z, float& ground);

private:

    typedef std::vector<Object*> Objects;
    World* m_world;
    Objects m_objects;
    Objects m_objectsToRemove;
    Objects m_activated;
};
