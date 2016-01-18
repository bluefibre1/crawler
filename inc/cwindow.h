#pragma once

#include "cobject.h"
#include "ccolor.h"
#include "cstring.h"

#include <vector>

class Window : public Object
{
public:
    Window();

    enum class VerticalAlign
    {
        TOP,
            CENTER,
            BOTTOM
    };

    enum class HorizontalAlign
    {
        LEFT,
            CENTER,
            RIGHT
    };

    void setVerticalAlign(VerticalAlign al);
    void setHorizontalAlign(HorizontalAlign al);
    void setMaxWidth(int width);
    void setBorderColor(Color color);
    void setBackground(Color color);

    void setBorderWidth(int h, int v);

    void clear();
    void print(Color color, const String& text);

    virtual void draw(Renderer* r) override;

    virtual void tick(float dt) override;

private:
    int m_width;
    int m_height;
    int m_hborder;
    int m_vborder;
    bool m_showBorder;
    int m_maxWidth;
    VerticalAlign m_valign;
    HorizontalAlign m_halign;
    Color m_borderColor;
    Color m_background;

    struct Print
    {
        String m_text;
        Color m_color;
    };
    std::vector<Print> m_prints;

    void internalDraw(Renderer* r);
    void pad(Renderer* r, Color c, int& x, int y);
    void print(Renderer* r, Color c, int& x, int y, const String& text);
    void topBorder(Renderer* r, int x, int& y);
    void bottomBorder(Renderer* r, int x, int& y);
    void leftBorder(Renderer* r, int& x, int y);
    void rightBorder(Renderer* r, int& x, int y);
    int getLineLength(int x);
    void newLine(int& x, int& y);
};

typedef std::shared_ptr<Window> WindowSharedPtr;
typedef std::weak_ptr<Window> WindowWeakPtr;
