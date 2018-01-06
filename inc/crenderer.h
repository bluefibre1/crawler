#pragma once

#include "ctile.h"
#include "cobject.h"
#include "cstring.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void clear();
    void flip();
    void draw(int x, int y, int z, const Tile* tile);
    void drawScreen(int x, int y, int z, const Tile* tile);
    void draw(int x, int y, int z, Color fg, Color bg, Char ch);
    void drawScreen(int x, int y, int z, Color fg, Color bg, Char ch);
    void draw(int x, int y, int z, Color fg, Color bg, const String& text);
    void drawScreen(int x, int y, int z, Color fg, Color bg, const String& text);
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    int getOriginX() const { return m_oX; }
    int getOriginY() const { return m_oY; }
    void setOrigin(int x, int y, int z) { m_oX = x; m_oY = y; m_oZ = z; }
    bool isVisible(Object* object) const;
    static int TOP();
    void showAsciiTable(int columns, int rows);

private:
    int m_width;
    int m_height;
    int m_oX;
    int m_oY;
    int m_oZ;

    struct Cell
    {
        Cell();
        Char m_ch;
        Color m_fg;
        Color m_bg;
        int m_z;
    };
    Cell* m_front;
    Cell* m_back;
    Cell m_empty;

    void size(int& w, int& h);
    bool raycast(int x, int y, int z);
};
