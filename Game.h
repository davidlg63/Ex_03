//
// Created by David on 25/06/2020.
//

#ifndef EX03_GAME_H
#define EX03_GAME_H

#include "Auxiliaries.h"
#include "Matrix.h"
#include "Character.h"
#include <memory>

namespace mtm
{
    class Game
    {
    private:
    Matrix<std::shared_ptr<mtm::Character>> board;
    int cpp_counter, python_counter;

    bool isInBoard(const GridPoint& coordinate) const;
    bool isCellEmpty(const GridPoint& coordinate) const;
    const std::string toCharArray() const;
    public:
        Game(int height, int width);
        ~Game() = default;
        Game(const Game& other);
        Game& operator=(const Game& other);

        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
        static std::shared_ptr<mtm::Character> makeCharacter(CharacterType type, Team team,
                                                        units_t health, units_t ammo, units_t range, units_t power);

        void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        void reload(const GridPoint & coordinates);

        friend std::ostream& operator<<(std::ostream& os, const Game& game);
        bool isOver(Team* winningTeam=NULL) const;
    };

    bool isIllegalInitialization(units_t health, units_t ammo, units_t range, units_t power);
}

#endif //EX03_GAME_H
