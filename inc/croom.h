#pragma once

#include "cobject.h"
#include "ctile.h"
#include "cstring.h"


class Room : public Object
{
public:
    Room();

    void setTilePtrSurface(const TilePtrSurface& surface);

    void setName(const String& name);

    virtual void draw(Renderer* r) override;

private:
    String m_name;
    TilePtrSurface m_surface;
};

typedef std::shared_ptr<Room> RoomSharedPtr;
