#pragma once

#include "cobject.h"
#include "ccolor.h"

#include <string>
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
    void setBackground(Color color);

    void setBorderWidth(int h, int v);

    void clear();
    void print(Color color, const std::string& text);

    virtual void draw(Renderer* r) override;

    virtual void tick(float dt) override;

private:
    int m_width;
    int m_height;
    int m_hborder;
    int m_vborder;
    int m_maxWidth;
    VerticalAlign m_valign;
    HorizontalAlign m_halign;
    Color m_background;

    struct Print
    {
        std::string m_text;
        Color m_color;
    };
    std::vector<Print> m_prints;

    void internalDraw(Renderer* r);
};
