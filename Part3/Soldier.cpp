//
// Created by X on 28/06/2020.
//

#include "Soldier.h"

namespace mtm{

    Soldier::Soldier(Team team, units_t  unit_health, units_t unit_ammo, units_t unit_range, units_t unit_power) :
            Character(team, unit_health, unit_ammo, unit_range, unit_power),collateral_dmg_range(ceil(unit_range/3))
    {
        print_representation = (team == PYTHON) ? 's' : 'S';
    }

    Soldier::Soldier(std::shared_ptr<Soldier> other) :
            Character(other->askTeam(), other->getHealth(), other->getAmmo(),
                      other->getRange(), other->getPower()), collateral_dmg_range(ceil(other->getRange()/3))
    {
        print_representation = (team == PYTHON) ? 's' : 'S';
    }


    Character* Soldier::clone() const
    {
        return new Soldier(*this);
    }

    void Soldier::attack(const GridPoint attacker, const GridPoint target, Matrix<std::shared_ptr<Character>>& board)
    {
        if(board(target.row,target.col)!=nullptr)
        {
            board(target.row,target.col)->setHealth(this->power);
        }
        this->ammo--;
        for (int i = target.row - collateral_dmg_range; i<2*collateral_dmg_range; i++)
        {
            for ( int j= target.col - collateral_dmg_range; j<2*collateral_dmg_range; j++)
            {
                if(i < 0 || i > board.height()-1 || j < 0 || j > board.width()-1)
                {
                    continue;
                }
                GridPoint collateral_damage(i,j);
                int distance=collateral_damage.distance(collateral_damage,target);
                if (distance != 0 && distance<=collateral_dmg_range && board(i,j)
                    != nullptr && board(i,j)->askTeam()!=team)
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
        int distance = GridPoint::distance(src_coordinates,dst_coordinates);
        return (distance <= this->range);
    }


}