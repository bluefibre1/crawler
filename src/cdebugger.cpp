#include "cdebugger.h"
#include "crenderer.h"
#include "ccolors.h"
#include "cstring.h"

Debugger::Debugger()
    : m_debugLevel(DebugLevel::OFF)
    , m_frameId(0)
    , m_objectTicked(0)
    , m_maxObjectTicked(0)
    , m_lastObjectTicked(0)
    , m_drawCalls(0)
    , m_maxDrawCalls(0)
    , m_lastDrawCalls(0)
    , m_drawSize(0)
    , m_maxDrawSize(0)
    , m_lastDrawSize(0)
    , m_remain(0)
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

void Debugger::cycleDebugLevel()
{
    switch (m_debugLevel)
    {
    case DebugLevel::OFF:
        m_debugLevel = DebugLevel::LOW;
        break;

    case DebugLevel::LOW:
        m_debugLevel = DebugLevel::MEDIUM;
        break;

    case DebugLevel::MEDIUM:
        m_debugLevel = DebugLevel::HIGH;
        break;

    case DebugLevel::HIGH:
        m_debugLevel = DebugLevel::OFF;
        break;
    }
}

void Debugger::setDebugLevel(DebugLevel lvl)
{
    m_debugLevel = lvl;
}

DebugLevel Debugger::getDebugLevel()
{
    return m_debugLevel;
}

void Debugger::incDrawCall()
{
    m_drawCalls++;
}

void Debugger::setDrawSize(int size)
{
    m_drawSize = size;
}

void Debugger::tick(float dt)
{
    if (m_debugLevel == DebugLevel::OFF)
    {
        return;
    }

    if (m_maxObjectTicked < m_objectTicked)
    {
        m_maxObjectTicked = m_objectTicked;
    }
    m_objectTicked = 0;

    if (m_maxDrawCalls < m_drawCalls)
    {
        m_maxDrawCalls = m_drawCalls;
    }
    m_drawCalls = 0;

    if (m_maxDrawSize < m_drawSize)
    {
        m_maxDrawSize = m_drawSize;
    }
    m_drawSize = 0;

    m_remain -= dt;
    if (m_remain < 0)
    {
        m_remain = 1;

        m_lastObjectTicked = m_maxObjectTicked;
        m_maxObjectTicked = 0;

        m_lastDrawCalls = m_maxDrawCalls;
        m_maxDrawCalls = 0;

        m_lastDrawSize = m_maxDrawSize;
        m_maxDrawSize = 0;
    }
}

void Debugger::draw(Camera* /*c*/, Renderer* r)
{
    if (m_debugLevel == DebugLevel::OFF)
    {
        return;
    }

    std::wstringstream s;
    s << "frame [f:" << m_frameId <<
        " o:"<< m_lastObjectTicked << "]" <<
        " draw[c:" << m_lastDrawCalls <<
        " s:" << m_lastDrawSize << "]";

    r->drawScreen(0, 0, Renderer::TOP(), Colors::YELLOW(), Colors::BLUE(), s.str());
}
