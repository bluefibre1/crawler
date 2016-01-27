#pragma once

#include "ccharactertemplate.h"

class CharacterTemplates
{
public:

    static const CharacterTemplateSharedPtr& DEMON();
    static const CharacterTemplateSharedPtr& VILLAGER();
    static const CharacterTemplateSharedPtr& KID();
    static const CharacterTemplateSharedPtr& BAT();

};

typedef std::vector<CharacterTemplateSharedPtr> CharacterTemplateSharedPtrs;
