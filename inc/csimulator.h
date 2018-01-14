#pragma once

#include "cobject.h"
#include "cworld.h"
#include <vector>

class Renderer;
class Character;
class Camera;

class Simulator
{
public:
    Simulator();

    static Simulator& get();

    void setWorld(const WorldSharedPtr& world);

    void add(const ObjectSharedPtr& object);

    void spawn(const ObjectSharedPtr& object);

    void remove(Object* object);

    void activate(Object* object);

    void tick(float dt);

    void draw(Camera* c, Renderer* r);

    bool isColliding(Object* collidee, int x, int y, int& z);

    bool listObjectsAt(int x, int y, int z, ObjectWeakPtrs* result);

    bool findObjectsAround(int x, int y, int z, float radius, ObjectWeakPtrs* result);

private:
    void initCell();
    int getCellIndex(int x, int y);

    int m_cellSize;
    int m_cellNumX;
    int m_cellNumY;
    int m_viewPortX;
    int m_viewPortY;
    int m_viewPortWidth;
    int m_viewPortHeight;
    typedef std::vector<ObjectSharedPtrs> ObjectCells;
    ObjectCells m_cells;
    WorldSharedPtr m_world;
    ObjectPtrs m_removed;
    ObjectPtrs m_activated;
};
