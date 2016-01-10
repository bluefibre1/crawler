#pragma once


class Color
{
public:
    Color();
    Color(int c);

    bool operator==(const Color& c) const;
    bool operator!=(const Color& c) const;

    int getValue() const { return m_color; }

private:
    int m_color;
};

enum class ColorStyle
{
    NORMAL=0,
        BRIGHT,
        DIM,
        INVALID
        };
