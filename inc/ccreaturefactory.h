#pragma once

class Creature;
class CreatureTemplate;

class CreatureFactory
{
public:

    static Creature* create(const CreatureTemplate* t);

};
