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
        static const int max_step_amount = 4;
        char print_representation;
        int shot_counter;
        std::shared_ptr<Character> clone() const;
    public:
        Sniper() = delete;
        Sniper(Team team, units_t  unit_health, units_t unit_ammo, units_t unit_range, units_t unit_power);
        Sniper(std::shared_ptr<Sniper> some_character);
        ~Sniper() override = default ;

        void reload() override;
        void attack(const GridPoint attacker,const GridPoint target,
                    Matrix<std::shared_ptr<Character>>& board, int& cpp_counter, int& python_counter) override;
        bool isInRange ( GridPoint src_coordinates, GridPoint dst_coordinates) const override;
        bool isStepLegal(const GridPoint& start, const GridPoint& end) const override;

        char toChar() const override
        {
            return this->print_representation;
        }

    };

}

#endif //PART3_SNIPER_H