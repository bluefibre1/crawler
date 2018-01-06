#include "cobject.h"
#include "csimulator.h"
#include "cdebugger.h"

Object::Object()
    : m_x(0)
    , m_y(0)
    , m_z(0)
    , m_dispX(0)
    , m_dispY(0)
{

}

Object::~Object()
{
}

void Object::tick(float /* dt */)
{
    CDEBUG_LOW(Debugger::get().incObjectTicked());
    if (m_dispX != 0 || m_dispY != 0)
    {
        Simulator::get().activate(this);
    }
}

bool Object::hasHint() const
{
    return false;
}

void Object::printHint(Window* /* w */) const
{

}
