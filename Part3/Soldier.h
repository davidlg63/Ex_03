//
// Created by X on 28/06/2020.
//

#ifndef PART3_SOLIDER_H
#define PART3_SOLIDER_H

#include "Character.h"
#include <cmath>

namespace mtm{

    class Soldier : public Character
    {
        static const int solider_reload_amount = 3;
        static const int max_step_amount = 3;
        const int collateral_dmg_range;
        char print_representation;
        static bool isValidTarget(const GridPoint& attacker, const GridPoint& target, const
        Matrix<std::shared_ptr<Character>>& board);
        static bool isInSameRowOrColumn(const GridPoint& attacker, const GridPoint& target, const
        Matrix<std::shared_ptr<Character>>& board);
        std::shared_ptr<Character> clone() const;
    public:
        Soldier() = delete;
        Soldier(Team team, units_t  unit_health, units_t unit_ammo, units_t unit_range, units_t unit_power);
        Soldier(std::shared_ptr<Soldier> some_character);
        Soldier(const Soldier&);
        ~Soldier() override = default ;
        void reload() override;
        void attack(const GridPoint attacker,const GridPoint target,
                    Matrix<std::shared_ptr<Character>>& board, int& cpp_counter, int& python_counter) override;
        void attackHalfHealth (std::shared_ptr<Character>& target);
        bool isInRange ( GridPoint src_coordinates, GridPoint dst_coordinates) const override;
        bool isStepLegal(const GridPoint &start, const GridPoint &end) const override;
        char toChar() const override
        {
            return this->print_representation;
        }

    };


}


#endif //PART3_SOLIDER_H