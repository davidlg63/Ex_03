//
// Created by X on 27/06/2020.
//

#ifndef PART3_GAME_H
#define PART3_GAME_H
#include "Auxiliaries.h"
#include <memory>
#include "Character.h"
#include "C:\Users\X\Desktop\ClionCodes\CLionProjects\hw3\Part2\Matrix.h"

namespace mtm {

    class Game {
        Matrix<std::shared_ptr<Character>> board;
        int height;
        int width;
        int phy_counter;
        int cpp_counter;

    public:

        Game(int height, int width);
        ~Game() = default;

        void addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character);
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                                                        units_t health, units_t ammo, units_t range, units_t power);

        void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        void reload(const GridPoint & coordinates);

        bool isOver(Team* winningTeam= nullptr) const;

        int Height() {
            return this->height;
        }

        int Width() {
            return this->width;
        }

        bool isOccupied(GridPoint coordinates);
        bool isLegalInitialization(units_t health, units_t ammo, units_t range, units_t power);
        bool isIllegalCell(GridPoint coordinates);
    };


}



#endif //PART3_GAME_H
