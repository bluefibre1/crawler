#pragma once

#include "croom.h"
#include "croomtemplate.h"

class RoomFactory
{
public:

    static RoomSharedPtr create(const RoomTemplateSharedPtr& t);

    static RoomSharedPtr createLandscape(const String& name, int size
        );

};
