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
    public:
        Character() = delete;
        Character(Team team, units_t  unit_health, units_t unit_ammo, units_t unit_power, units_t unit_range);
        virtual ~Character();
        virtual std::shared_ptr<Character> clone() const;
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

    class Solider : Character
    {
        static int solider_reload_amount;
        char print_representation;
        int collateral_dmg_range;
    public:
        Solider() = delete;
        Solider(Team team, units_t  unit_health, units_t unit_ammo, units_t unit_power, units_t unit_range);
        Solider(std::shared_ptr<Solider> some_character);
        ~Solider() override = default ;
        std::shared_ptr<Character> clone() const override ;
       // Solider& operator=( std::shared_ptr<Character> some_character) override ;
        void reload() override;
        void attack (const GridPoint attacker, const GridPoint target, Matrix<std::shared_ptr<Character>> board) override ;
        void attackHalfHealth (std::shared_ptr<Character> target);
        bool isInRange ( GridPoint src_coordinates, GridPoint dst_coordinates) const override ;

        char toChar() const override
        {
            return this->print_representation;
        }

    };

    class Medic : Character {
        static int medic_reload_amount;
        char print_representation;
    public:
        Medic() = delete ;
        Medic(Team team, units_t unit_health, units_t unit_ammo, units_t unit_power, units_t unit_range);
        Medic(std::shared_ptr<Medic> some_character);
        std::shared_ptr<Character> clone() const override ;
        ~Medic() override = default;
        //Medic &operator=(std::shared_ptr<Character> some_character) override;
        void reload() override;
        void attack(const GridPoint attacker, const GridPoint target, Matrix<std::shared_ptr<Character>> board) override;
        bool isInRange(GridPoint src_coordinates, GridPoint dst_coordinates) const override;

        char toChar() const override {
            return this->print_representation;
        }

    };

        class Sniper :Character {
            static int min_range;
            static int Sniper_reload_amount;
            char print_representation;
            int shot_counter;
        public:
        Sniper() = delete;
            Sniper(Team team, units_t  unit_health, units_t unit_ammo, units_t unit_power, units_t unit_range);
            Sniper(std::shared_ptr<Sniper> some_character);
            std::shared_ptr<Character> clone() const override;
            ~Sniper() override = default ;
           // Sniper& operator=( std::shared_ptr<Character> some_character) override ;
            void reload() override;
            void attack (const GridPoint attacker, const GridPoint target, Matrix<std::shared_ptr<Character>> board) override;
            bool isInRange ( GridPoint src_coordinates, GridPoint dst_coordinates) const override ;

            char toChar() const override
            {
                return this->print_representation;
            }

    };
}


#endif //PART3_CHARACTER_H
