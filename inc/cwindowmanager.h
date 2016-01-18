#pragma once

#include "cwindow.h"
#include "ctimer.h"

#include <vector>

class Renderer;

class WindowManager
{
public:

    static WindowManager& get();

    void popup(const WindowSharedPtr& window, float period);

    void tick(float dt);

    void draw(Renderer* r);

private:
    struct Popup
    {
        WindowSharedPtr m_window;
        Timer m_timer;
        float m_period;
    };

    std::vector<Popup*> m_popups;

    WindowManager();
    ~WindowManager();
};
