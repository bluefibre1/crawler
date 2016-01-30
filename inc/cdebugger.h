#pragma once

class Renderer;

class Debugger
{
public:
    static Debugger& get();

    void incFrameId();
    int getFrameId();

    void incObjectTicked();

    void toggleDebugInfo();
    bool isDebugInfoEnabled();

    void draw(Renderer* r);

private:
    Debugger();

    bool m_debugInfoEnabled;
    int m_frameId;
    int m_objectTicked;
};

#define CDEBUG(...)                               \
    do                                            \
    {                                             \
        if (Debugger::get().isDebugInfoEnabled()) \
        {                                         \
            __VA_ARGS__;                          \
        }                                         \
    }                                             \
    while (0)
