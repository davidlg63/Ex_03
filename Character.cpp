//
// Created by X on 27/06/2020.
//

#include "Character.h"
#include <cmath>


namespace  mtm {
    Character::Character(Team team, units_t unit_health, units_t unit_ammo, units_t unit_range, units_t unit_power) :
            team(team), health(unit_health), ammo(unit_ammo), power(unit_power), range(unit_range) {}

    Character &Character::operator=(const std::shared_ptr<Character> other)
    {
        std::shared_ptr<Character> tmp = nullptr;
        try {
            tmp = std::shared_ptr<Character>(other->clone());
        }
        catch (const std::bad_alloc &memory_error) {
            throw memory_error;
        }
        delete this;
        return *tmp;
    }

    Character::Character(const mtm::Character &other) : team(other.team), health(other.health), ammo(other.ammo),
    power(other.power), range(other.range) {}

    void Character::remove(const GridPoint &coordinate, Matrix<std::shared_ptr<Character>>& board,
        int &cpp_counter, int &python_counter)
    {
        (team == CPP) ? cpp_counter-- : python_counter--;
        board(coordinate.row, coordinate.col) = nullptr;
    }
}