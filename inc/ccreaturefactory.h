#pragma once

#include "ccreature.h"

class CreatureTemplate;

class CreatureFactory
{
public:

    static CreaturePtr create(const CreatureTemplate* t);

};
