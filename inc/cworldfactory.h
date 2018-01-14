#pragma once

#include "cworld.h"

class WorldCreateParams
{
public:
    WorldCreateParams(const String& name, unsigned int size);

    const String& getName() const { return m_name;}

    unsigned int getSize() const { return m_size; }

private:
    String m_name;
    unsigned int m_size;
};

class WorldFactory
{
public:

    static WorldSharedPtr create(const WorldCreateParams& params);

};
