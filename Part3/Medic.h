//
// Created by X on 28/06/2020.
//

#ifndef PART3_MEDIC_H
#define PART3_MEDIC_H

#include "Character.h"

namespace  mtm
{

    class Medic : public Character
    {
        static const int medic_reload_amount = 5;
        static const int max_step_amount = 5;
        char print_representation;
        std::shared_ptr<Character> clone() const;
    public:
        Medic() = delete ;
        Medic(Team team, units_t unit_health, units_t unit_ammo, units_t unit_range, units_t unit_power);
        Medic(std::shared_ptr<Medic> some_character);
        ~Medic() override = default;
        //Medic &operator=(std::shared_ptr<Character> some_character) override;
        void reload() override;
        void attack(const GridPoint attacker,const GridPoint target,
                    Matrix<std::shared_ptr<Character>>& board, int& cpp_counter, int& python_counter) override;
        bool isInRange(GridPoint src_coordinates, GridPoint dst_coordinates) const override;
        bool isStepLegal(const GridPoint &start, const GridPoint &end) const override;
        char toChar() const override {

            return this->print_representation;
        }
    };

}

#endif //PART3_MEDIC_H