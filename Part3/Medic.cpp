//
// Created by X on 28/06/2020.
//

#include "Medic.h"
#include "Exception.h"

namespace mtm
{

    Medic::Medic(Team team, units_t  unit_health, units_t unit_ammo, units_t unit_power, units_t unit_range):
            Character(team, unit_health, unit_ammo, unit_power, unit_range)
    {
        if (team==PYTHON) {
            this->print_representation = 'm';
        }
        this->print_representation ='M';
    }

    Medic::Medic(std::shared_ptr<Medic> some_character) :
            Character(some_character->askTeam(), some_character->getHealth(), some_character->getAmmo(),
                      some_character->getPower(), some_character->getRange())
    {
        if (team==PYTHON)
        {
            this->print_representation = 'm';
        }
        this->print_representation ='M';
    }

    Character* Medic::clone() const
    {
        return new Medic(*this);
    }

    void Medic::reload()
    {
        this->ammo+=medic_reload_amount;
    }

    void Medic::attack(const GridPoint attacker, const GridPoint target, Matrix<std::shared_ptr<Character>> board)
    {
        if (attacker == target)
        {
            throw IllegalTarget();
        }
        if (board(attacker.row,attacker.col)->askTeam()==board(target.row,target.col)->askTeam())
        {
            board(target.row,target.col)->setHealth(-this->power);
            return;
        }
        board(target.row,target.col)->setHealth(this->power);
        this->ammo--;

    }

    bool Medic::isInRange(GridPoint src_coordinates, GridPoint dst_coordinates) const
    {
        return src_coordinates.distance(src_coordinates,dst_coordinates)<=range;
    }

}