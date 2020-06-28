//
// Created by X on 27/06/2020.
//

#include "Character.h"
#include <cmath>


namespace  mtm {

    Character::Character(Team team, units_t  unit_health, units_t unit_ammo, units_t unit_power, units_t unit_range) :
    team(team), health(unit_health), ammo(unit_ammo), power(unit_power), range(unit_range)
    {};

    Character& Character::operator=(const std::shared_ptr<Character> some_character)
    {
        try
        {
        std::shared_ptr<Character> tmp(new Character(some_character->askTeam(),some_character->getHealth(),
                some_character->getAmmo(),some_character->getPower(), some_character->getRange());
        }
        catch   (const std::bad_alloc& memory_error)
        {
            throw memory_error;
        }
        delete this;
        return *tmp;
    }
    template <class T> const
    <T> Character::clone()
    {
        return new T(*this);
    }


}