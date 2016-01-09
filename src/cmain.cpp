#include "crenderer.h"
#include "cworld.h"
#include "chero.h"
#include "cinput.h"
#include "ctimer.h"
#include "csimulator.h"
#include "ccreature.h"

#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
    srand(time(nullptr));

    int x, y;
    Input input;
    Renderer r;
    World world;
    Hero hero;

    world.generate(1024);

    Creature testMonster;
    testMonster.setPosition(105, 100, world.getHeightAt(105, 100));
    testMonster.setBehavior(new BehaviorWander());

    hero.setPosition(100, 100, world.getHeightAt(100, 100));

    Simulator* simulator = Simulator::get();
    simulator->setWorld(&world);
    simulator->addCollider(&hero);
    simulator->addCollider(&testMonster);

    Timer timer;
    while (!input.quit())
    {
        float dt = timer.elapsed();
        timer.reset();

        world.tick(dt);
        hero.tick(dt);
        testMonster.tick(dt);
        simulator->tick(dt);

        // control camera around hero
        int centerX = hero.getX() - r.getWidth() / 2;
        int centerY = hero.getY() - r.getHeight() / 2;
        /*
          int ox = r.getOriginX();
          int oy = r.getOriginY();
          int errX = (int)fabs((float)centerX - ox) - r.getWidth() / 6;
          int errY = (int)fabs((float)centerY - oy) - r.getHeight() / 6;
          if (errX > 0)
          {
          ox += (centerX > ox) ? errX : -errX;
          }

          if (errY > 0)
          {
          oy += (centerY > oy) ? errY : -errY;
          }

          r.setOrigin(ox, oy);
        */
        r.setOrigin(centerX, centerY, hero.getZ());

        r.clear();
        world.draw(&r);
        hero.draw(&r);
        testMonster.draw(&r);
        r.flip();

        int sleepTime = (int)(33333.3f - timer.elapsed() * 1000000.0f);
        if (sleepTime > 0)
        {
            usleep(sleepTime);
        }
    }

    return 0;
}
