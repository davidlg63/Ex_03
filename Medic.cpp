//
// Created by X on 28/06/2020.
//

#include "Medic.h"

namespace mtm
{

    Medic::Medic(Team team, units_t  unit_health, units_t unit_ammo, units_t unit_range, units_t unit_power):
            Character(team, unit_health, unit_ammo, unit_range, unit_power)
    {
        print_representation = (team == PYTHON) ? 'm' : 'M';
    }

    Medic::Medic(std::shared_ptr<Medic> some_character) :
            Character(some_character->askTeam(), some_character->getHealth(), some_character->getAmmo(),
                      some_character->getRange(), some_character->getPower())
    {
        print_representation = (team == PYTHON) ? 'm' : 'M';
    }

    std::shared_ptr<Character> Medic::clone() const
    {
        return std::make_shared<Medic>(*this);
    }

    void Medic::reload()
    {
        this->ammo+=medic_reload_amount;
    }

    void Medic::attack(const GridPoint attacker,const GridPoint target, Matrix<std::shared_ptr<Character>>& board,
            int& cpp_counter, int& python_counter)
    {
        if (attacker == target || board(target.row, target.col) == nullptr)
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
        if(board(target.row, target.col)->getHealth() <= 0)
        {
            board(target.row, target.col)->remove(target, board, cpp_counter, python_counter);
        }
    }

    bool Medic::isInRange(GridPoint src_coordinates, GridPoint dst_coordinates) const
    {
        return src_coordinates.distance(src_coordinates,dst_coordinates)<=range;
    }

}