//
// Created by X on 28/06/2020.
//

#ifndef PART3_SNIPER_H
#define PART3_SNIPER_H

#include "Character.h"
namespace mtm
{

    class Sniper : public Character
    {
        int min_range;
        static const int Sniper_reload_amount = 2;
        char print_representation;
        int shot_counter;
        Character* clone() const;
    public:
        Sniper() = delete;
        Sniper(Team team, units_t  unit_health, units_t unit_ammo, units_t unit_power, units_t unit_range);
        Sniper(std::shared_ptr<Sniper> some_character);
        ~Sniper() override = default ;

        void reload() override;
        void attack ( GridPoint attacker,  GridPoint target, Matrix<std::shared_ptr<Character>> board) override;
        bool isInRange ( GridPoint src_coordinates, GridPoint dst_coordinates) const override ;

        char toChar() const override
        {
            return this->print_representation;
        }

    };

}
#endif //PART3_SNIPER_H
