#include "crenderer.h"
#include "cworldfactory.h"
#include "chero.h"
#include "cinput.h"
#include "ctimer.h"
#include "csimulator.h"
#include "ccharacterfactory.h"
#include "ccharactertemplates.h"
#include "citemfactory.h"
#include "cmath.h"
#include "ctiles.h"
#include "ccolors.h"
#include "clogger.h"
#include "cwindowmanager.h"
#include "cchestfactory.h"
#include "cdebugger.h"
#include "croomfactory.h"
#include "croomtemplates.h"
#include "ccamera.h"

#include <unistd.h>

int main(int /*argc*/, char* /*argv*/[])
{
    srand(time(nullptr));

    Logger::get().setLevel(LogLevel::DEBUG);
    CLOG_DEBUG(CHAR_T("starting crawler"));

    Input input;
    Camera c;
    Renderer r;
     // r.showAsciiTable(12, 1000);
     // return 0;

    auto& simulator = Simulator::get();
    auto& windowManager = WindowManager::get();

    // Possibility: 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096...
    WorldCreateParams worldParams(CHAR_T("IceLand"), 64);
    WorldSharedPtr world = WorldFactory::create(worldParams);
    simulator.setWorld(world);

    HeroSharedPtr hero(new Hero());
    hero->setMapHp(100);
    hero->heal();
    hero->setName(CHAR_T("Hero"));
    hero->equip(ItemFactory::create(ItemTemplates::PUNCH()));
    simulator.spawn(hero);
    c.setSubject(hero);

    CharacterTemplateSharedPtrs creatureTemplates;
    creatureTemplates.push_back(CharacterTemplates::DEMON());
    creatureTemplates.push_back(CharacterTemplates::VILLAGER());
    creatureTemplates.push_back(CharacterTemplates::KID());
    creatureTemplates.push_back(CharacterTemplates::BAT());

    int worldArea = world->getWidth() * world->getHeight();

    float creatureDensity = 0 / (float)(64*64);
    int numCreature = (int)(worldArea * creatureDensity);
    for (int i = 0; i < numCreature; i++)
    {
        int idx = Math::ceilRandom(creatureTemplates.size());
        ObjectSharedPtr creature(CharacterFactory::create(creatureTemplates[idx]));
        simulator.spawn(creature);
    }

    float chestDensity = 7 / (float)(64*64);
    int numChest = (int)(worldArea * chestDensity);
    for (int i = 0; i < numChest; i++)
    {
        ObjectSharedPtr chest(ChestFactory::create());
        simulator.spawn(chest);
    }

    Debugger& debugger = Debugger::get();

    Timer timer;
    while (!input.quit())
    {
        debugger.incFrameId();
        float dt = timer.elapsed();
        timer.reset();

        CDEBUG_LOW(debugger.tick(dt));

        simulator.tick(dt);
        windowManager.tick(dt);

        c.draw(&r);
        simulator.draw(&c, &r);
        windowManager.draw(&c, &r);
        CDEBUG_LOW(debugger.draw(&c, &r));
        r.flip();

        int sleepTime = (int)(33333.3f - timer.elapsed() * 1000000.0f);
        if (sleepTime > 0)
        {
            usleep(sleepTime);
        }
    }

    return 0;
}
