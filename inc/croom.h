#pragma once

#include "cobject.h"
#include "ctile.h"


class Room : public Object
{
public:
    Room();

    void setTilePtrSurface(const TilePtrSurface& surface);

    virtual void draw(Renderer* r) override;

private:
    TilePtrSurface m_surface;
};
