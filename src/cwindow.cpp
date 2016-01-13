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
    , m_maxWidth(20)
    , m_valign(VerticalAlign::TOP)
    , m_halign(HorizontalAlign::LEFT)
    , m_background(Colors::COOL_BLUE())
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

void Window::print(Color color, const std::string& text)
{
    Print p;
    p.m_color = color;
    p.m_text = text;
    m_prints.push_back(p);
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
    using namespace std;

    float x = getX();
    float y = getY();
    int lineLength = 0;
    for (auto i = m_prints.begin(); i != m_prints.end(); ++i)
    {
        const Print& p = *i;

        istringstream iss(p.m_text);
        vector<string> words{istream_iterator<string>{iss},
                istream_iterator<string>{}};

        for (auto j = words.begin(); j != words.end(); ++j)
        {
            string& word = *j;
            if (lineLength + word.size() >= m_maxWidth)
            {
                if (lineLength < m_width)
                {
                    string padding(m_width - lineLength, ' ');
                    r->drawText(x, y, p.m_color, m_background, padding);
                }
                y++;
                x = getX();
            }
            r->drawText(x + lineLength, y, p.m_color, m_background, word);
            lineLength += word.size();
        }

        if (lineLength < m_width)
        {
            string padding(m_width - lineLength, ' ');
            r->drawText(x + lineLength, y, p.m_color, m_background, padding);
        }

    }
}

void Window::tick(float dt)
{

}
