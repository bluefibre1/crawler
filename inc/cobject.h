#pragma once

#include <memory>

class Renderer;

class Object
{
public:
    Object();
    virtual ~Object();

    virtual void draw(Renderer* r) {};

    virtual void tick(float dt);

    void setPosition(float x, float y, float z) { m_x = x; m_y = y; m_z = z; }

    int getX() const { return m_x; }

    int getY() const { return m_y; }

    int getZ() const { return m_z; }

    void setDisplacement(int x, int y) { m_dispX = x; m_dispY = y; }

    void stop() { setDisplacement(0,0); }

    float getDisplacementX() const { return m_dispX; }

    float getDisplacementY() const { return m_dispY; }

    virtual bool isCharacter() const { return false; }

private:
    int m_x;
    int m_y;
    int m_z;

    int m_dispX;
    int m_dispY;
};

typedef std::shared_ptr<Object> ObjectPtr;
typedef std::weak_ptr<Object> ObjectWeakPtr;
