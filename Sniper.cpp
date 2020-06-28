//
// Created by X on 28/06/2020.
//

#include "Character.h"
namespace mtm
{

    Sniper::Sniper(Team team, units_t  unit_health, units_t unit_ammo, units_t unit_power, units_t unit_range):
            Character(team, unit_health, unit_ammo, unit_power, unit_range), shot_counter(0)
    {
        Sniper_reload_amount=2;
        min_range=(this->getRange()/2);
        if (team==PYTHON) {
            this->print_representation = 'n';
        }
        this->print_representation ='N';
    }

    Sniper::Sniper(std::shared_ptr<Sniper> some_character) :
            Character(some_character->askTeam(), some_character->getHealth(), some_character->getAmmo(),
                      some_character->getPower(), some_character->getRange()), shot_counter(0)
    {
        Sniper_reload_amount=2;
        min_range=(this->getRange()/2);
        if (team==PYTHON) {
            this->print_representation = 'n';
        }
        this->print_representation ='N';
    }

    std::shared_ptr<Character> Sniper::clone() const
    {
        return   std::shared_ptr<Character>(new Sniper(*this));
    }

    void Sniper::reload()
    {
        this->ammo+=Sniper_reload_amount;
    }

    void Sniper::attack(const GridPoint attacker, const GridPoint target, Matrix<std::shared_ptr<Character>> board)
    {
        this->shot_counter++;
        shot_counter%3==0?  board(attacker.row,attacker.col)->setHealth(2*this->power)
                         : board(attacker.row,attacker.col)->setHealth(this->power);
        this->ammo--;

    }

    bool Sniper::isInRange(GridPoint src_coordinates, GridPoint dst_coordinates) const
    {
        int distance = src_coordinates.distance(src_coordinates, dst_coordinates);
        return (distance <= this->range && distance >= this->min_range);
    }

}