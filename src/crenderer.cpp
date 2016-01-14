#include "crenderer.h"

#include "ctiles.h"
#include "ccolors.h"

#include <termcap.h>
#include <cstddef>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <stdlib.h>


Renderer::Cell::Cell()
    : m_ch(' ')
    , m_fg(Colors::BLACK())
    , m_bg(Colors::BLACK())
    , m_z(INT_MIN)
{
}

static char TERMINAL_CAP_BUFFER[2048];

Renderer::Renderer()
    : m_width(0)
    , m_height(0)
    , m_oX(0)
    , m_oY(0)
    , m_oZ(0)
    , m_front(nullptr)
    , m_back(nullptr)
    , m_empty()
{
    m_empty.m_ch = Tiles::EMPTY.getValue();
    m_empty.m_fg = Tiles::EMPTY.getForeground();
    m_empty.m_bg = Tiles::EMPTY.getBackground();

    clear();
}

Renderer::~Renderer()
{
    delete [] m_front;
    delete [] m_back;
}

void Renderer::clear()
{
    int w, h;
    size(w, h);
    int n = w*h;
    if (m_width != w || m_height != h || !m_back || !m_front)
    {
        m_width = w;
        m_height = h;

        delete [] m_back;
        delete [] m_front;

        m_back = new Cell[n];
        for (int i = 0; i < n; i++)
        {
            m_back[i].m_ch = 0;
        }

        m_front = new Cell[n];
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            m_front[i] = m_empty;
        }
    }
}

void Renderer::flip()
{
    int lastH = -1;
    int lastW = -1;
    int n = m_width*m_height;
    for (int h = 0; h < m_height; h++)
    {
        for (int w = 0; w < m_width; w++)
        {
            int i = w + h * m_width;
            assert(i < n);
            const Cell* f = &m_front[i];
            if (raycast(w, h, f->m_z))
            {
                f = &m_empty;
            }

            const Cell* b = &m_back[i];
            if (f->m_ch != b->m_ch ||
                f->m_fg != b->m_fg ||
                f->m_bg != b->m_bg)
            {
                if (lastH != h || lastW != w)
                {
                    printf("\033[%d;%dH", h+1, w+1);
                    lastH = h;
                    lastW = w;
                }

                if (f->m_fg != Colors::INVALID())
                {
                    setFg(f->m_fg);
                }

                if (f->m_bg != Colors::INVALID())
                {
                    setBg(f->m_bg);
                }

                printf("%c", f->m_ch);
                lastW++;
            }
        }
    }

    Cell* tmp = m_back;
    m_back = m_front;
    m_front = tmp;

    fflush(stdout);
}

void Renderer::draw(int x, int y, int z, const Tile* tile)
{
    int ox = x - m_oX;
    int oy = y - m_oY;

    if (ox >= 0 && oy >= 0 && ox < m_width && oy < m_height)
    {
        int i = ox + oy * m_width;
        Cell& c = m_front[i];
        if (z >= c.m_z)
        {
            c.m_ch = tile->getValue();
            if (tile->getForeground() != Colors::INVALID())
            {
                c.m_fg = tile->getForeground();
            }

            if (tile->getBackground() != Colors::INVALID())
            {
                c.m_bg = tile->getBackground();
            }

            c.m_z = z;
        }
    }
}

void Renderer::drawChar(int x, int y, int z, Color fg, Color bg, char ch)
{
    int ox = x - m_oX;
    int oy = y - m_oY;

    if (ox >= 0 && oy >= 0 && ox < m_width && oy < m_height)
    {
        int i = ox + oy * m_width;
        Cell& c = m_front[i];
        if (z >= c.m_z)
        {
            c.m_ch = ch;
            if (fg != Colors::INVALID())
            {
                c.m_fg = fg;
            }

            if (bg != Colors::INVALID())
            {
                c.m_bg = bg;
            }

            c.m_z = z;
        }
    }
}

void Renderer::drawText(int x, int y, Color fg, Color bg, const std::string& text)
{
    int n = text.size();
    if (x + n > m_width)
    {
        n = x > m_width ? 0 : m_width - x;
    }

    for (int i = 0; i < n; i++)
    {
        int idx = (x + i) + y * m_width;
        Cell& c = m_front[idx];

        c.m_ch = text[i];

        if (fg != Colors::INVALID())
        {
            c.m_fg = fg;
        }

        if (bg != Colors::INVALID())
        {
            c.m_bg = bg;
        }

        c.m_z = 0x7FFFFFFF;
    }
}

bool Renderer::isVisible(Object* object) const
{
    int x = object->getX() - m_oX;
    int y = object->getY() - m_oY;
    return x >= 0 && x < m_width && y >= 0 && y < m_height;
}

void Renderer::size(int& w, int& h)
{
    char* termtype = getenv("TERM");

    if (tgetent(TERMINAL_CAP_BUFFER, termtype) >= 0)
    {
        h = tgetnum((char*)"li");
        w = tgetnum((char*)"co");
    }
    else
    {
        w = 30;
        h = 20;
    }
}

void Renderer::setFg(Color color)
{
    printf("\033[38;5;%im", color.getValue());
}

void Renderer::setBg(Color color)
{
    printf("\033[48;5;%im", color.getValue());
}

bool Renderer::raycast(int x, int y, int z)
{
    /*
      int ox = m_width / 2;
      int oy = m_height / 2;

      int dx = x - ox;
      int dy = y - oy;
      int dz = z - m_oZ;
      bool rising = false;

      if (dx > dy)
      {
      float steps = dx > 0 ? dx : -dx;
      int stepX = dx > 0 ? 1 : -1;
      float stepY = dy / steps;
      float stepZ = dz / steps;
      int cx = ox;
      float cy = oy;
      float cz = m_oZ;
      for (int i = 1; i < steps; ++i)
      {
      cx += stepX;
      cy += stepY;
      cz += stepZ;

      int idx = cx + (int)cy * m_width;
      const Cell& c = m_front[idx];

      //printf("\033[%d;%dH*", (int)cy+1, (int)cx+1);

      if (c.m_z > cz)
      {
      stepZ = 0;
      cz = c.m_z;
      rising = true;
      return true;
      }
      else if (rising)
      {
      return true;
      }
      }
      }
      else
      {
      float steps = dy > 0 ? dy : -dy;
      float stepX = dx / steps;
      int stepY = dy > 0 ? 1 : -1;
      float stepZ = dz / steps;
      float cx = ox;
      int cy = oy;
      float cz = m_oZ;
      for (int i = 1; i < steps; ++i)
      {
      cx += stepX;
      cy += stepY;
      cz += stepZ;

      int idx = (int)cx + cy * m_width;
      const Cell& c = m_front[idx];

      //printf("\033[%d;%dH*", (int)cy+1, (int)cx+1);

      if (c.m_z > cz)
      {
      stepZ = 0;
      cz = c.m_z;
      rising = true;
      return true;
      }
      else if (rising)
      {
      return true;
      }
      }
      }
    */
    return false;
}
