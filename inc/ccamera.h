#pragma once

#include "cobject.h"

class Renderer;

class Camera
{
public:
    void draw(Renderer* r);

    void setSubject(const ObjectSharedPtr& subject) { m_subject = subject; }

    const ObjectSharedPtr& getSubject() const { return m_subject; }

private:
    ObjectSharedPtr m_subject;
};
