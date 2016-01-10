#include "crenderer.h"
#include "cworld.h"
#include "chero.h"
#include "cinput.h"
#include "ctimer.h"
#include "csimulator.h"
#include "ccreaturefactory.h"
#include "ccreaturetemplates.h"
#include "ccreature.h"
#include "cmath.h"
#include "ctiles.h"
#include "ccolors.h"

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

    Simulator* simulator = Simulator::get();

    World world;
    world.generate(128);
    simulator->setWorld(&world);

    Hero* hero = new Hero();
    simulator->spawn(hero);

    const CreatureTemplate* creatureTemplates[] = {
        &CreatureTemplates::DRAGON,
        &CreatureTemplates::VILLAGER,
        &CreatureTemplates::KID
    };

    for (int i = 0; i < 100; i++)
    {
        int numTemplates = sizeof(creatureTemplates) / sizeof(CreatureTemplates*);
        int idx = Math::ceilRandom(numTemplates);
        Creature* creature = CreatureFactory::create(creatureTemplates[idx]);
        simulator->spawn(creature);
    }

    Timer timer;
    while (!input.quit())
    {
        float dt = timer.elapsed();
        timer.reset();
        simulator->tick(dt);

        // control camera around hero
        int centerX = hero->getX() - r.getWidth() / 2;
        int centerY = hero->getY() - r.getHeight() / 2;
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
        r.setOrigin(centerX, centerY, hero->getZ());

        r.clear();
        simulator->draw(&r);
        r.flip();

        int sleepTime = (int)(33333.3f - timer.elapsed() * 1000000.0f);
        if (sleepTime > 0)
        {
            usleep(sleepTime);
        }
    }

    return 0;
}
