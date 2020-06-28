//
// Created by X on 27/06/2020.
//

#ifndef PART3_CHARACTER_H
#define PART3_CHARACTER_H
#include "Auxiliaries.h"
#include <memory>
#include "Game.h"



namespace mtm {

    class Character
    {
    protected:
        Team team;
        units_t health, ammo, power, range;
        template <class>
        virtual Character* clone() const =0;
    public:
        Character() = delete;
        Character(Team team, units_t  unit_health, units_t unit_ammo, units_t unit_power, units_t unit_range);
        virtual ~Character();
        virtual Character* clone() const;
        Character& operator=(const std::shared_ptr<Character> some_character);
        virtual bool isInRange(const GridPoint src_coordinates,const GridPoint dst_coordinates) const;
        virtual  void reload();
        virtual char toChar() const;
        virtual  void attack(const GridPoint attacker, const GridPoint target, Matrix<std::shared_ptr<Character>> board);

        Team askTeam() const  {
            return this->team;
        }

        units_t getRange() const  {
            return this->range;
        }

        units_t getAmmo() const  {
            return this->range;
        }

        units_t getHealth() const  {
            return this->health;
        }

        void setHealth(int num)  {
            this->health -= num;
        }

        units_t getPower() const  {
            return this->power;
        }

        bool isOutOfAmmo() const  {
            return ammo == 0;
        }
    };
}


#endif //PART3_CHARACTER_H
