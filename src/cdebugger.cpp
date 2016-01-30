#include "cdebugger.h"
#include "crenderer.h"
#include "ccolors.h"
#include "cstring.h"

Debugger::Debugger()
    : m_debugInfoEnabled(false)
    , m_frameId(0)
    , m_objectTicked(0)
{

}

Debugger& Debugger::get()
{
    static Debugger instance;
    return instance;
}

void Debugger::incFrameId()
{
    m_frameId++;
}

int Debugger::getFrameId()
{
    return m_frameId;
}

void Debugger::incObjectTicked()
{
    m_objectTicked++;
}

void Debugger::toggleDebugInfo()
{
    m_debugInfoEnabled = !m_debugInfoEnabled;
}

bool Debugger::isDebugInfoEnabled()
{
    return m_debugInfoEnabled;
}

void Debugger::draw(Renderer* r)
{
    std::stringstream s;
    s << "Frame:" << m_frameId << " Ticked:"<< m_objectTicked;
    r->drawScreen(0, 0, Renderer::TOP(), Colors::YELLOW(), Colors::BLUE(), s.str());

    m_objectTicked = 0;
}
