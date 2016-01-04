#pragma once

#include "cobject.h"
#include "cworld.h"
#include <vector>

class Simulator
{
 public:

  static Simulator* get();

  void setWorld(World* world);
  
  void addCollider(Object* object);

  void removeCollider(Object* object);
  
  void activate(Object* object);

  void tick(float dt);
  
 private:
  typedef std::vector<Object*> Objects;
  World* m_world;
  Objects m_objects;  
  Objects m_colliders;
  Objects m_collidersToRemove;
};
