//
// Created by X on 28/06/2020.
//

#include "Sniper.h"
namespace mtm
{

    Sniper::Sniper(Team team, units_t  unit_health, units_t unit_ammo, units_t unit_range, units_t unit_power):
            Character(team, unit_health, unit_ammo, unit_range, unit_power), shot_counter(0)
    {
        min_range=ceil(((double)(this->getRange())/2));
        print_representation = (team == PYTHON) ? 'n' : 'N';
    }

    Sniper::Sniper(std::shared_ptr<Sniper> some_character) :
            Character(some_character->askTeam(), some_character->getHealth(), some_character->getAmmo(),
                      some_character->getRange(), some_character->getPower()), shot_counter(0)
    {
        min_range=ceil(((double)(this->getRange())/2));
        print_representation = (team == PYTHON) ? 'n' : 'N';
    }

    std::shared_ptr<Character> Sniper::clone() const
    {
        return std::make_shared<Sniper>(*this);
    }

    void Sniper::reload()
    {
        this->ammo+=Sniper_reload_amount;
    }

    void Sniper::attack(const GridPoint attacker_point,const GridPoint target_point,
                Matrix<std::shared_ptr<Character>>& board, int& cpp_counter, int& python_counter)
    {
        std::shared_ptr<Character> attacker = board(attacker_point.row, attacker_point.col);
        std::shared_ptr<Character> target = board(target_point.row, target_point.col);
        if(target == nullptr || attacker->askTeam() == target->askTeam())
        {
            throw IllegalTarget();
        }
        this->shot_counter++;
        shot_counter%3==0 ? target->setHealth(2*this->power)
                         : target->setHealth(this->power);
        this->ammo--;
        if(target->getHealth() <= 0)
        {
            target->remove(target_point, board, cpp_counter, python_counter);
        }
    }

    bool Sniper::isInRange(GridPoint src_coordinates, GridPoint dst_coordinates) const
    {
        int distance = src_coordinates.distance(src_coordinates, dst_coordinates);
        return (distance <= this->range && distance >= this->min_range);
    }

}