
#include "cwindow.h"
#include "crenderer.h"
#include "ccolors.h"
#include "cmath.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

Window::Window()
    : m_alignedX(0)
    , m_alignedY(0)
    , m_width(0)
    , m_height(0)
    , m_hborder(0)
    , m_vborder(0)
    , m_showBorder(true)
    , m_maxWidth(20)
    , m_valign(VerticalAlign::TOP)
    , m_halign(HorizontalAlign::LEFT)
    , m_borderColor(Colors::WHITE())
    , m_background(Colors::BLACK())
    , m_title()
    , m_prints()
{

}

void Window::setTitle(const String& title)
{
    m_title = title;
}

void Window::setVerticalAlign(VerticalAlign al)
{
    m_valign = al;
}

void Window::setHorizontalAlign(HorizontalAlign al)
{
    m_halign = al;
}

void Window::setMaxWidth(int width)
{
    m_maxWidth = width;
}

int Window::getWidth()
{
    if (m_width == 0)
    {
        internalDraw(nullptr);
    }
    return m_width;
}

int Window::getHeight()
{
    if (m_height == 0)
    {
        internalDraw(nullptr);
    }
    return m_height;
}

void Window::clear()
{
    m_prints.clear();
}

void Window::print(Color color, const String& text)
{
    Print p;
    p.m_color = color;
    p.m_text = text;
    m_prints.push_back(p);
}

void Window::printEndLine()
{
    Print p;
    p.m_text = '\n';
    m_prints.push_back(p);
}

void Window::setBorderColor(Color color)
{
    m_borderColor = color;
}

void Window::setBackground(Color color)
{
    m_background = color;
}

void Window::setBorderWidth(int h, int v)
{
    m_hborder = h;
    m_vborder = v;
}

void Window::draw(Camera* /*c*/, Renderer* r)
{
    m_width = 0;
    m_height = 0;
    internalDraw(nullptr);
    internalDraw(r);
}

void Window::tick(float /*dt*/)
{

}

void Window::internalDraw(Renderer* r)
{
    if (r)
    {
        switch (m_halign)
        {
        default:
        case HorizontalAlign::LEFT:
            m_alignedX = getX();
            break;

        case HorizontalAlign::CENTER:
            m_alignedX = (r->getWidth() - m_width) / 2;
            break;

        case HorizontalAlign::RIGHT:
            m_alignedX = r->getWidth() - getX() - m_width;
            break;
        }

        switch (m_valign)
        {
        default:
        case VerticalAlign::TOP:
            m_alignedY = getY();
            break;

        case VerticalAlign::CENTER:
            m_alignedY = (r->getHeight() - m_height) / 2;
            break;

        case VerticalAlign::BOTTOM:
            m_alignedY = r->getHeight() - getY() - m_height;
            break;
        }
    }

    Color c;
    int x = m_alignedX;
    int y = m_alignedY;

    topBorder(r, x, y);
    for (auto i = m_prints.begin(); i != m_prints.end(); ++i)
    {
        const Print& p = *i;
        c = p.m_color;

        if (x == m_alignedX)
        {
            leftBorder(r, x, y);
        }

        const Char* ch = p.m_text.c_str();

        String word;
        while (*ch)
        {
            word.clear();

            do
            {
                word += *ch;
                ch++;
            }
            while (*ch && *ch != ' ' && *ch != '\n');

            if (*word.c_str() != '\n')
            {
                if (getLineLength(x) + (int)word.size() >= m_maxWidth)
                {
                    pad(r, c, x, y);
                    rightBorder(r, x, y);
                    newLine(r, x, y);
                }
                print(r, c, x, y, word);
            }
            else
            {
                pad(r, c, x, y);
                rightBorder(r, x, y);
                newLine(r, x, y);
            }
        }
    }

    pad(r, c, x, y);
    rightBorder(r, x, y);
    newLine(r, x, y);
    bottomBorder(r, x, y);
}

void Window::pad(Renderer* r, Color c, int& x, int y)
{
    int n = m_width - getLineLength(x) - m_vborder - (m_showBorder ? 1 : 0);
    if (n > 0)
    {
        if (r)
        {
            r->drawScreen(x, y, Renderer::TOP(), c, m_background, String(n, ' '));
        }
        x += n;
    }
}

void Window::print(Renderer* r, Color c, int& x, int y, const String& text)
{
    if (r && !text.empty())
    {
        r->drawScreen(x, y, Renderer::TOP(), c, m_background, text);
    }
    x += text.size();
}

void Window::topBorder(Renderer* r, int x, int& y)
{
    if (m_showBorder)
    {
        if (r && m_width)
        {
            r->drawScreen(x, y, Renderer::TOP(), m_borderColor, m_background, '+');
            if (!m_title.empty())
            {
                int padding = (m_width - 2 > (int)m_title.size() ?
                                   (m_width - 2 - (int)m_title.size()) / 2 : 0) - 1;
                r->drawScreen(x+1, y, Renderer::TOP(), m_borderColor, m_background, String(padding, '-'));
                r->drawScreen(x+padding+1, y, Renderer::TOP(), m_borderColor, m_background, ' ');
                r->drawScreen(x+padding+2, y, Renderer::TOP(), m_borderColor, m_background, m_title);
                r->drawScreen(x+padding+2+m_title.size(), y, Renderer::TOP(), m_borderColor, m_background, ' ');
                r->drawScreen(x+padding+2+m_title.size()+1, y, Renderer::TOP(), m_borderColor, m_background,
                            String(padding + (m_width % 2 ? 1:0), '-'));
            }
            else
            {
                r->drawScreen(x+1, y, Renderer::TOP(), m_borderColor, m_background, String(m_width-2, '-'));
            }

            r->drawScreen(x + m_width - 1, y, Renderer::TOP(), m_borderColor, m_background, '+');
        }
        else if (m_width < (int)m_title.size() + 6)
        {
            m_width = m_title.size() + 6;
        }
        newLine(r, x, y);

        for (int i = 0; i < m_hborder; ++i)
        {
            leftBorder(r, x, y);
            pad(r, m_background, x, y);
            rightBorder(r, x, y);
            newLine(r, x, y);
        }
    }
}

void Window::bottomBorder(Renderer* r, int x, int& y)
{
    if (m_showBorder)
    {
        for (int i = 0; i < m_hborder; ++i)
        {
            leftBorder(r, x, y);
            pad(r, m_background, x, y);
            rightBorder(r, x, y);
            newLine(r, x, y);
        }

        if (r)
        {
            r->drawScreen(x, y, Renderer::TOP(), m_borderColor, m_background, '+');
            r->drawScreen(x+1, y, Renderer::TOP(), m_borderColor, m_background, String(m_width - 2, '-'));
            r->drawScreen(x + m_width - 1, y, Renderer::TOP(), m_borderColor, m_background, '+');
        }
        newLine(r, x, y);
    }
}

void Window::leftBorder(Renderer* r, int& x, int y)
{
    if (m_showBorder)
    {
        if (r)
        {
            r->drawScreen(x, y, Renderer::TOP(), m_borderColor, m_background, '|');
            if (m_vborder)
            {
                r->drawScreen(x+1, y, Renderer::TOP(), m_borderColor, m_background, String(m_vborder, ' '));
            }
        }

        x++;
    }
    x += m_vborder;
}

void Window::rightBorder(Renderer* r, int& x, int y)
{
    if (m_showBorder)
    {
        if (r)
        {
            if (m_vborder)
            {
                r->drawScreen(x, y, Renderer::TOP(), m_borderColor, m_background, String(m_vborder, ' '));
            }
            r->drawScreen(x+(m_vborder ? 1 : 0), y, Renderer::TOP(), m_borderColor, m_background, '|');
        }

        x++;
    }
    x += m_vborder;
}

int Window::getLineLength(int x)
{
    return x - m_alignedX;
}

void Window::newLine(Renderer* r, int& x, int& y)
{
    y++;
    if (!r)
    {
        if (getLineLength(x) > m_width)
        {
            m_width = getLineLength(x);
            if (m_width > m_maxWidth)
            {
                m_width = m_maxWidth;
            }
        }
        m_height++;
    }
    x = m_alignedX;
}
