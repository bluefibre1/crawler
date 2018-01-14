#pragma once

#include "croomtemplate.h"

class RoomTemplates
{
public:

    static const RoomTemplateSharedPtr& INN();

    static const RoomTemplateSharedPtr& DUNGEON_ROOM_LEFT();
    static const RoomTemplateSharedPtr& DUNGEON_ROOM_RIGHT();
    static const RoomTemplateSharedPtr& DUNGEON_ROOM_UP();
    static const RoomTemplateSharedPtr& DUNGEON_ROOM_DOWN();

    static const RoomTemplateSharedPtr& DUNGEON_CROSS();
    static const RoomTemplateSharedPtr& DUNGEON_TEE_LEFT();
    static const RoomTemplateSharedPtr& DUNGEON_TEE_RIGHT();
    static const RoomTemplateSharedPtr& DUNGEON_TEE_UP();
    static const RoomTemplateSharedPtr& DUNGEON_TEE_DOWN();

    static const RoomTemplateSharedPtr& DUNGEON_CORRIDOR_HORIZONTAL();
    static const RoomTemplateSharedPtr& DUNGEON_CORRIDOR_VERTICAL();


};
