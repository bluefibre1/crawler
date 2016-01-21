#pragma once

#include "cobject.h"
#include "ccolor.h"
#include "cstring.h"

#include <vector>

class Window : public Object
{
public:
    Window();

    enum class VerticalAlign : int
    {
        TOP=0,
            CENTER,
            BOTTOM,
            MAX
    };

    enum class HorizontalAlign : int
    {
        LEFT=0,
            CENTER,
            RIGHT,
            MAX
    };

    void setTitle(const String& title);
    void setVerticalAlign(VerticalAlign al);
    VerticalAlign getVerticalAlign() const { return m_valign; }
    void setHorizontalAlign(HorizontalAlign al);
    HorizontalAlign getHorizontalAlign() const { return m_halign; }
    void setMaxWidth(int width);
    void setBorderColor(Color color);
    void setBackground(Color color);

    void setBorderWidth(int h, int v);

    int getWidth();
    int getHeight();

    void clear();
    void print(Color color, const String& text);

    virtual void draw(Renderer* r) override;

    virtual void tick(float dt) override;

private:
    int m_alignedX;
    int m_alignedY;
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
    String m_title;

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
    void newLine(Renderer* r, int& x, int& y);
};

typedef std::shared_ptr<Window> WindowSharedPtr;
typedef std::weak_ptr<Window> WindowWeakPtr;
