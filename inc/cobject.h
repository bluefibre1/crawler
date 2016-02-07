#pragma once

#include "cstring.h"
#include <memory>
#include <vector>

class Renderer;
class Window;

class Object
{
public:
    Object();
    virtual ~Object();

    virtual void draw(Renderer* /*r*/) {};

    virtual void tick(float dt);

    void setPosition(float x, float y, float z) { m_x = x; m_y = y; m_z = z; }

    int getX() const { return m_x; }

    int getY() const { return m_y; }

    int getZ() const { return m_z; }

    void setDisplacement(int x, int y) { m_dispX = x; m_dispY = y; }

    void stop() { setDisplacement(0,0); }

    float getDisplacementX() const { return m_dispX; }

    float getDisplacementY() const { return m_dispY; }

    enum ObjectType
    {
        OBJECT_TYPE_UNKNOWN   = 0x0,
        OBJECT_TYPE_CHEST     = 0x1,
        OBJECT_TYPE_CHARACTER = 0x2,
        OBJECT_TYPE_HERO      = 0x4,
    };

    virtual int getObjectType() const { return OBJECT_TYPE_UNKNOWN; }

    virtual bool isCollidable() const { return true; }

    virtual bool hasHint() const;

    virtual void printHint(Window* w) const;

private:
    int m_x;
    int m_y;
    int m_z;

    int m_dispX;
    int m_dispY;
};

typedef std::shared_ptr<Object> ObjectSharedPtr;
typedef std::weak_ptr<Object> ObjectWeakPtr;

typedef std::vector<Object*> ObjectPtrs;
typedef std::vector<ObjectWeakPtr> ObjectWeakPtrs;
typedef std::vector<ObjectSharedPtr> ObjectSharedPtrs;
