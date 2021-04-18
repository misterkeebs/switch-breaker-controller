#ifndef SCREEN_H
#define SCREEN_H

#include <Colors.h>
#include <Gfx.h>

class Screen
{
  public:
    virtual int draw() {
      return -1;
    }
};

#endif
