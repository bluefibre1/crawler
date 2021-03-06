#include "cwindowmanager.h"
#include "crenderer.h"
#include "ccolors.h"

WindowManager::WindowManager()
    : m_popups()
{

}

WindowManager::~WindowManager()
{
    for (auto i = m_popups.begin(); i != m_popups.end(); ++i)
    {
        delete *i;
    }
}

WindowManager& WindowManager::get()
{
    static WindowManager inst;
    return inst;
}

void WindowManager::popup(const WindowSharedPtr& window, float period)
{
    Popup* p = nullptr;
    for (auto i = m_popups.begin(); i != m_popups.end(); ++i)
    {
        if ((*i)->m_window == window)
        {
            p = *i;
            break;
        }
    }

    if (!p)
    {
        p = new Popup();
        p->m_window = window;
        m_popups.push_back(p);
    }

    p->m_period = period;
    p->m_timer.reset();
}

void WindowManager::tick(float dt)
{
    for (int i = 0; i < (int)m_popups.size(); )
    {
        Popup* p = m_popups[i];
        if (p->m_timer.elapsed() < p->m_period)
        {
            p->m_window->tick(dt);
            i++;
        }
        else
        {
            delete p;
            m_popups.erase(m_popups.begin() + i);
        }
    }
}

void WindowManager::draw(Camera* c, Renderer* r)
{
    const int numAlign = (int)Window::VerticalAlign::MAX +
        (int)Window::HorizontalAlign::MAX * (int)Window::VerticalAlign::MAX;

    int xos[numAlign] = {2};
    int yos[numAlign] = {2};
    for (int i = 0; i < numAlign; ++i)
    {
        xos[i] = 2;
        yos[i] = 1;
    }

    for (auto i = m_popups.begin(); i != m_popups.end(); ++i)
    {
        Popup* p = *i;
        Window* w = p->m_window.get();

        int alignIdx = (int)w->getVerticalAlign() +
            (int)w->getHorizontalAlign() * (int)Window::VerticalAlign::MAX;

        int& xOffset = xos[alignIdx];
        int& yOffset = yos[alignIdx];

        w->setPosition(xOffset, yOffset, 0);
        yOffset += w->getHeight() + 1;
        w->draw(c, r);
    }
}
