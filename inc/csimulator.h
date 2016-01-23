#pragma once

#include "cobject.h"
#include "cworld.h"
#include <vector>

class Renderer;
class Character;

class Simulator
{
public:

    static Simulator& get();

    void setWorld(const WorldSharedPtr& world);

    void add(const ObjectSharedPtr& object);

    void spawn(const ObjectSharedPtr& object);

    void remove(Object* object);

    void activate(Object* object);

    void tick(float dt);

    void draw(Renderer* r);

    bool isColliding(Object* collidee, int x, int y, int& z);

    bool listObjectsAt(int x, int y, int z, ObjectWeakPtrs* result);

    bool findObjectsAround(int x, int y, int z, float sqrRadius, ObjectWeakPtrs* result);

private:

    WorldSharedPtr m_world;
    ObjectSharedPtrs m_objects;
    ObjectPtrs m_removed;
    ObjectPtrs m_activated;
};
