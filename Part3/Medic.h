//
// Created by X on 28/06/2020.
//

#ifndef PART3_MEDIC_H
#define PART3_MEDIC_H

#include "Character.h"

namespace  mtm
{

    class Medic : Character {
        static int medic_reload_amount;
        char print_representation;
        Character* clone() const;
    public:
        Medic() = delete ;
        Medic(Team team, units_t unit_health, units_t unit_ammo, units_t unit_power, units_t unit_range);
        Medic(std::shared_ptr<Medic> some_character);
        ~Medic() override = default;
        //Medic &operator=(std::shared_ptr<Character> some_character) override;
        void reload() override;
        void attack(const GridPoint attacker, const GridPoint target, Matrix<std::shared_ptr<Character>> board) override;
        bool isInRange(GridPoint src_coordinates, GridPoint dst_coordinates) const override;

        char toChar() const override {

            return this->print_representation;
        }
    };

}

#endif //PART3_MEDIC_H
