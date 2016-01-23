#pragma once

enum class Key : int
{
    UP = 0,
        DOWN,
        LEFT,
        RIGHT
        };

class Input
{
public:
    Input();

    static bool getKey(int& key);

    static bool quit();
    static void setQuit();

    static bool isPaused();
    static void setPause(bool pause);

private:
    static int kbhit();
    static int getch();
    static void reset();

    static bool m_quit;

    static bool m_pause;
};
