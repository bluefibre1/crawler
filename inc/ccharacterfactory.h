#pragma once

#include "ccharactertemplate.h"
#include "ccharacter.h"

class CharacterFactory
{
public:

    static CharacterSharedPtr create(const CharacterTemplateSharedPtr& t);

};
