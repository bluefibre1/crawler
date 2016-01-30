#pragma once

#include "croom.h"
#include "croomtemplate.h"

class RoomFactory
{
public:

    static RoomSharedPtr createRoom(const RoomTemplateSharedPtr& t);

};
