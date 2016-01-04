#include "cinput.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <stdio.h>

static struct termios m_origTermios;  

bool Input::m_quit = false;

Input::Input()
{
  struct termios newTermios;

  /* take two copies - one for now, one for later */
  tcgetattr(0, &m_origTermios);
  memcpy(&newTermios, &m_origTermios, sizeof(newTermios));

  /* register cleanup handler, and set the new terminal mode */
  atexit(Input::reset);
  cfmakeraw(&newTermios);
  newTermios.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(0, TCSANOW, &newTermios);

  printf("\e[?25l");
  fflush(stdout);
}

void Input::reset()
{
  tcsetattr(0, TCSANOW, &m_origTermios);
  printf("\033[0m");
  printf("\e[?25h");
  fflush(stdout) ;
}

bool Input::quit()
{
  return m_quit;
}

void Input::setQuit()
{
  m_quit = true;
}

bool Input::getKey(int& key)
{
  if (!kbhit())
    {
      return false;
    }

  int ch = getch();
  if (ch == 27)
    {
      if (getch() == 91)
	{
	  switch (getch())
	    {
	    case 'A':
	      key = (int)Key::UP;
	      break;

	    case 'B':
	      key = (int)Key::DOWN;
	      break;

	    case 'C':
	      key = (int)Key::RIGHT;
	      break;

	    case 'D':
	      key = (int)Key::LEFT;
	      break;
	    }
	}
    }
  else
    {
      key = ch;
    }
  
  return true; 
}

int Input::kbhit()
{
  struct timeval tv = { 0L, 0L };
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(0, &fds);
  return select(1, &fds, NULL, NULL, &tv);
}

int Input::getch()
{
  int r;
  unsigned char c;
  if ((r = read(0, &c, sizeof(c))) < 0) {
    return r;
  } else {
    return c;
  }
}
