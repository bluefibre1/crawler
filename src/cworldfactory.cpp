#include "cworldfactory.h"

#include "cmath.h"
#include "ctiles.h"
#include "croomtemplates.h"
#include "croomfactory.h"

WorldCreateParams::WorldCreateParams(const String& name, unsigned int size)
    : m_name(name)
    , m_size(size)
{

}

WorldSharedPtr WorldFactory::create(const WorldCreateParams& params)
{
    WorldSharedPtr world(new World(params.getSize()));

    auto landscape = RoomFactory::createLandscape(params.getName(), params.getSize());
    world->addOnTop(0, 0, landscape);

    for (int i = 0; i < 1; i++)
    {
        auto room = RoomFactory::create(RoomTemplates::INN());
        world->addOnTop(0, 0, room);
    }

    return world;
}

