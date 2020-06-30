//
// Created by X on 28/06/2020.
//

#include "Soldier.h"

namespace mtm{

    Soldier::Soldier(Team team, units_t  unit_health, units_t unit_ammo, units_t unit_range, units_t unit_power) :
            Character(team, unit_health, unit_ammo, unit_range, unit_power),
            collateral_dmg_range(ceil((double)unit_range/3))
    {
        print_representation = (team == PYTHON) ? 's' : 'S';
    }

    Soldier::Soldier(std::shared_ptr<Soldier> other) :
            Character(other->askTeam(), other->getHealth(), other->getAmmo(), other->getRange(), other->getPower()),
            collateral_dmg_range(ceil(other->getRange()/3))
    {
        print_representation = (team == PYTHON) ? 's' : 'S';
    }

    Soldier::Soldier(const Soldier &other) : Soldier(other.team, other.health, other.ammo, other.range, other.power)
    {}


    std::shared_ptr<Character> Soldier::clone() const
    {
        return std::make_shared<Soldier>(*this);
    }

    void Soldier::attack(const GridPoint attacker,const GridPoint target,
                     Matrix<std::shared_ptr<Character>>& board, int& cpp_counter, int& python_counter)
    {
        if(!isInSameRowOrColumn(attacker, target, board))
        {
            throw IllegalTarget();
        }
        this->ammo--;
        if(isValidTarget(attacker, target, board))
        {
            board(target.row,target.col)->setHealth(this->power);
            if(board(target.row, target.col)->getHealth() <= 0)
            {
                board(target.row, target.col)->remove(target, board, cpp_counter, python_counter);
            }
        }
        for (int i = target.row - collateral_dmg_range; i <= target.row + collateral_dmg_range; i++)
        {
            for ( int j= target.col - collateral_dmg_range; j <= target.col + collateral_dmg_range; j++)
            {
                if(i < 0 || i > board.height()-1 || j < 0 || j > board.width()-1)
                {
                    continue;
                }
                GridPoint collateral_damage(i,j);
                int distance = GridPoint::distance(collateral_damage,target);
                if (distance != 0 && distance<=collateral_dmg_range && isValidTarget(attacker,collateral_damage,board))
                {
                    attackHalfHealth(board(i,j));
                    if (board(i,j)->getHealth()<=0)
                    {
                        board(i,j)->remove(GridPoint(i,j), board, cpp_counter, python_counter);
                    }
                }
            }
        }
    }

    void Soldier::attackHalfHealth (std::shared_ptr<Character>& target)
    {
        target->setHealth(ceil((double)(this->power) / 2));
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

    bool Soldier::isStepLegal(const GridPoint &start, const GridPoint &end) const
    {
        return (GridPoint::distance(start, end) <= max_step_amount);
    }

    bool Soldier::isValidTarget(const GridPoint& attacker, const GridPoint& target, const
    Matrix<std::shared_ptr<Character>>& board)
    {
        return(board(target.row, target.col) != nullptr && !(attacker == target)
        && board(attacker.row, attacker.col)->askTeam() != board(target.row, target.col)->askTeam());
    }

    bool Soldier::isInSameRowOrColumn(const GridPoint &attacker, const GridPoint &target,
                                      const Matrix<std::shared_ptr<Character>> &board)
    {
        return (attacker.row == target.row || attacker.col == target.col);
    }
}