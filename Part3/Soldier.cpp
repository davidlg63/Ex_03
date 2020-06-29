//
// Created by X on 28/06/2020.
//

#include "Soldier.h"

namespace mtm{

    Soldier::Soldier(Team team, units_t  unit_health, units_t unit_ammo, units_t unit_power, units_t unit_range) :
            Character(team, unit_health, unit_ammo, unit_power, unit_range),collateral_dmg_range(ceil(unit_range/3))
    {
        if (team==PYTHON)
        {
            this->print_representation = 's';
        }
        this->print_representation ='S';
    }

    Soldier::Soldier(std::shared_ptr<Soldier> other) :
            Character(other->askTeam(), other->getHealth(), other->getAmmo(),
                      other->getPower(), other->getRange()), collateral_dmg_range(ceil(other->getRange()/3))
    {
        if (team==PYTHON)
        {
            this->print_representation = 's';
        }
        this->print_representation ='S';
    }


    Character* Soldier::clone() const
    {
        return new Soldier(*this);
    }

    void Soldier::attack(const GridPoint attacker, const GridPoint target, Matrix<std::shared_ptr<Character>> board)
    {
        board(target.row,target.col)->setHealth(this->power);
        this->ammo--;
        for (int i = target.row - range; i<2*range; i++)
        {
            for ( int j= target.col - range; j<2*range; j++)
            {
                GridPoint collateral_damage(i,j);
                int distance=collateral_damage.distance(collateral_damage,target);
                if (distance != 0 && distance<=collateral_dmg_range && board(i,j)
                    != nullptr && board(i,j)->askTeam()==team)
                {
                    attackHalfHealth(board(i,j));
                    if (board(i,j)->getHealth()<=0)
                    {
                        board(i,j)= nullptr;
                    }
                }
            }
        }
    }

    void Soldier::attackHalfHealth (std::shared_ptr<Character> target)
    {
        target->setHealth(this->power/2);
    }

    void Soldier::reload()
    {
        this->ammo+=solider_reload_amount;
    }

    bool Soldier::isInRange (const GridPoint src_coordinates,const GridPoint dst_coordinates) const
    {
        if (!(src_coordinates.row == dst_coordinates.row && src_coordinates.col == dst_coordinates.col))
        {
            return false;
        }
        int distance=src_coordinates.distance(src_coordinates,dst_coordinates);
        return (distance <= this->range);
    }


}