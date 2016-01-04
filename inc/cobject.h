#pragma once

class Renderer;

class Object
{
 public:
  Object();
  virtual ~Object() {}
  
  virtual void draw(Renderer* r) {};

  virtual void tick(float dt);
  
  void setPosition(float x, float y, float z) { m_x = x; m_y = y; m_z = z; }

  float getX() const { return m_x; }

  float getY() const { return m_y; }

  float getZ() const { return m_z; }

  void setVelocity(float x, float y, float z) { m_velX = x; m_velY = y; m_velZ = z; }

  void stop() { setVelocity(0,0,0); }

  float getVelocityX() const { return m_velX; }

  float getVelocityY() const { return m_velY; }

  float getVelocityZ() const { return m_velZ; }

  void setFriction(float f) { m_friction = f; }

  float getFriction() const { return m_friction; }
  
 private:
  float m_x;
  float m_y;
  float m_z;

  float m_velX;
  float m_velY;
  float m_velZ;

  float m_friction;
};
