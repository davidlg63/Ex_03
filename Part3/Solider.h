//
// Created by X on 28/06/2020.
//

#ifndef PART3_SOLIDER_H
#define PART3_SOLIDER_H

#include "Character.h"

namespace mtm{

    class Solider : Character
    {
        static int solider_reload_amount;
        char print_representation;
        int collateral_dmg_range;
       Character* clone() const;
    public:
        Solider() = delete;
        Solider(Team team, units_t  unit_health, units_t unit_ammo, units_t unit_power, units_t unit_range);
        Solider(std::shared_ptr<Solider> some_character);
        ~Solider() override = default ;
        void reload() override;
        void attack (const GridPoint attacker, const GridPoint target, Matrix<std::shared_ptr<Character>> board) override ;
        void attackHalfHealth (std::shared_ptr<Character> target);
        bool isInRange ( GridPoint src_coordinates, GridPoint dst_coordinates) const override ;

        char toChar() const override
        {
            return this->print_representation;
        }

    };


}


#endif //PART3_SOLIDER_H
