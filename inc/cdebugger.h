#pragma once

class Camera;
class Renderer;

enum class DebugLevel : int
{
    OFF = 0,
    LOW,
        MEDIUM,
        HIGH,
};

class Debugger
{
public:
    static Debugger& get();

    void incFrameId();
    int getFrameId();

    void incObjectTicked();

    void cycleDebugLevel();
    void setDebugLevel(DebugLevel lvl);
    DebugLevel getDebugLevel();

    void incDrawCall();
    void setDrawSize(int size);

    void tick(float dt);
    void draw(Camera* c, Renderer* r);

private:
    Debugger();

    DebugLevel m_debugLevel;
    int m_frameId;
    int m_objectTicked;
    int m_maxObjectTicked;
    int m_lastObjectTicked;
    int m_drawCalls;
    int m_maxDrawCalls;
    int m_lastDrawCalls;
    int m_drawSize;
    int m_maxDrawSize;
    int m_lastDrawSize;
    float m_remain;
};

#define CDEBUG(lvl, ...)                            \
    do                                              \
    {                                               \
        if (Debugger::get().getDebugLevel() >= lvl) \
        {                                           \
            __VA_ARGS__;                            \
        }                                           \
    }                                               \
    while (0)

#define CDEBUG_LOW(...) CDEBUG(DebugLevel::LOW, __VA_ARGS__)
#define CDEBUG_MEDIUM(...) CDEBUG(DebugLevel::MEDIUM, __VA_ARGS__)
#define CDEBUG_HIGH(...) CDEBUG(DebugLevel::HIGH, __VA_ARGS__)
