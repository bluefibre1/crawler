#pragma once

#include "croom.h"
#include "croomtemplate.h"

class RoomFactory
{
public:

    static RoomSharedPtr create(const RoomTemplateSharedPtr& t);

private:
    static void createSurface(const Strings& surface, TilePtrSurface& out);
};
