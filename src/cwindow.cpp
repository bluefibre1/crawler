#include "cwindow.h"
#include "crenderer.h"
#include "ccolors.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

Window::Window()
    : m_width(1)
    , m_height(1)
    , m_hborder(0)
    , m_vborder(0)
    , m_showBorder(true)
    , m_maxWidth(20)
    , m_valign(VerticalAlign::TOP)
    , m_halign(HorizontalAlign::LEFT)
    , m_borderColor(Colors::WHITE())
    , m_background(Colors::BLACK())
    , m_prints()
{

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

void Window::draw(Renderer* r)
{
    m_width = 1;
    internalDraw(nullptr);
    internalDraw(r);
}

void Window::tick(float /*dt*/)
{

}

void Window::internalDraw(Renderer* r)
{
    using namespace std;

    Color c;
    int x = getX();
    int y = getY();

    topBorder(r, x, y);
    for (auto i = m_prints.begin(); i != m_prints.end(); ++i)
    {
        const Print& p = *i;
        c = p.m_color;

        if (x == getX())
        {
            leftBorder(r, x, y);
        }

        if (p.m_text != "\n")
        {
            istringstream iss(p.m_text);
            vector<string> words{istream_iterator<string>{iss},
                    istream_iterator<string>{}};

            for (auto j = words.begin(); j != words.end(); ++j)
            {
                string& word = *j;

                if (getLineLength(x) + (int)word.size() >= m_maxWidth)
                {
                    pad(r, c, x, y);
                    rightBorder(r, x, y);
                    newLine(x, y);
                }

                print(r, c, x, y, word);
            }
        }
        else
        {
            pad(r, c, x, y);
            rightBorder(r, x, y);
            newLine(x, y);
        }
    }

    pad(r, c, x, y);
    rightBorder(r, x, y);
    newLine(x, y);
    bottomBorder(r, x, y);
}

void Window::pad(Renderer* r, Color c, int& x, int y)
{
    int n = m_width - getLineLength(x) - m_vborder - (m_showBorder ? 1 : 0);
    if (n > 0)
    {
        if (r)
        {
            r->drawText(x, y, c, m_background, String(n, ' '));
        }
        x += n;
    }
}

void Window::print(Renderer* r, Color c, int& x, int y, const String& text)
{
    if (r && !text.empty())
    {
        r->drawText(x, y, c, m_background, text);
    }
    x += text.size();
}

void Window::topBorder(Renderer* r, int x, int& y)
{
    if (m_showBorder && r)
    {
        r->drawChar(x, y, m_borderColor, m_background, '+');
        r->drawText(x+1, y, m_borderColor, m_background, String(m_width - 2, '-'));
        r->drawChar(x + m_width - 1, y, m_borderColor, m_background, '+');
        newLine(x, y);
        for (int i = 0; i < m_hborder; ++i)
        {
            leftBorder(r, x, y);
            pad(r, m_background, x, y);
            rightBorder(r, x, y);
            newLine(x, y);
        }
    }
}

void Window::bottomBorder(Renderer* r, int x, int& y)
{
    if (m_showBorder && r)
    {
        for (int i = 0; i < m_hborder; ++i)
        {
            leftBorder(r, x, y);
            pad(r, m_background, x, y);
            rightBorder(r, x, y);
            newLine(x, y);
        }
        r->drawChar(x, y, m_borderColor, m_background, '+');
        r->drawText(x+1, y, m_borderColor, m_background, String(m_width - 2, '-'));
        r->drawChar(x + m_width - 1, y, m_borderColor, m_background, '+');
    }
}

void Window::leftBorder(Renderer* r, int& x, int y)
{
    if (m_showBorder)
    {
        if (r)
        {
            r->drawChar(x, y, m_borderColor, m_background, '|');
            if (m_vborder)
            {
                r->drawText(x+1, y, m_borderColor, m_background, String(m_vborder, ' '));
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
                r->drawText(x, y, m_borderColor, m_background, String(m_vborder, ' '));
            }
            r->drawChar(x+(m_vborder ? 1 : 0), y, m_borderColor, m_background, '|');
        }

        x++;
    }
    x += m_vborder;
}

int Window::getLineLength(int x)
{
    return x - getX();
}

void Window::newLine(int& x, int& y)
{
    y++;
    if (getLineLength(x) > m_width)
    {
        m_width = getLineLength(x);
        if (m_width > m_maxWidth)
        {
            m_width = m_maxWidth;
        }
    }
    x = getX();
}
