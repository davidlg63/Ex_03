//
// Created by X on 27/06/2020.
//

#include "Game.h"
#include "Solider.h"
#include "Sniper.h"
#include "Medic.h"

namespace  mtm
{
    void Game::addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character) {

        /*if(isIllegalCell(coordinates))
        {
            throw IllegalCell();
        }
        if (isOccupied(coordinates))
        {
            throw CellOccupied();
        }*/

        this->board(coordinates.row, coordinates.col) = character;
    }

    std::shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team,
                                                   units_t health, units_t ammo, units_t range, units_t power)
    {
        /*
         if (!(isLegalInitialization(health,ammo,range,power))
          {
              throw IllegalArgument();
          } */

        switch (type) {
            case SOLDIER :
                return std::shared_ptr<Solider>(new Solider(team, health, ammo, power, range));

            case MEDIC :
                return std::shared_ptr<Medic>(new Medic(team, health, ammo, power, range));

            case SNIPER:
                return std::shared_ptr<Sniper>(new Sniper(team, health, ammo, power, range));
        }
    }

    void Game::move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
    {
        /*if (isIllegalCell(dst_coordinates))
        {
            throw IllegalCell();
        }
        if (!(isOccupied(src_coordinates)))
        {
            throw CellEmpty();
        }
        if (!(board(src_coordinates.row,src_coordinates.col)->isInRange(src_coordinates,dst_coordinates))
        {
            throw MoveTooFar;
        }
        if (isOccupied(dst_coordinates))
        {
            throw CellOccupied();
        }*/

        board(dst_coordinates.row,dst_coordinates.col)=board(src_coordinates.row,src_coordinates.col);
        board(src_coordinates.row,src_coordinates.col)= nullptr;
    }

    void Game::reload(const GridPoint & coordinates)
    {
        /*if (isIllegalCell(coordinates))
        {
            throw IllegalCell();
        }
        if (!(isOccupied(coordinates)))
        {
            throw CellEmpty();
        }*/
        board(coordinates.row,coordinates.col)->reload();
    }

    bool Game::isOver(Team* winningTeam) const
    {
        if (winningTeam != nullptr)
        {
            if (cpp_counter == 0 && phy_counter != 0) {
                *winningTeam = PYTHON;
                return true;
            } else if ((cpp_counter != 0 && phy_counter == 0)) {
                *winningTeam = CPP;
                return true;
            }
            return false;
        }
        return ((cpp_counter == 0 && phy_counter != 0) || (cpp_counter != 0  && phy_counter == 0));
    }


    bool Game::isOccupied(GridPoint coordinates) {
        return !(this->board(coordinates.row, coordinates.col) == nullptr);
    }

    bool Game::isIllegalCell(GridPoint coordinates) {
        return (coordinates.row < 0 || coordinates.row > height || coordinates.col < 0 || coordinates.col > width);
    }

    bool Game::isLegalInitialization(units_t health, units_t ammo, units_t range, units_t power) {
        return (health <= 0 || ammo<0 || range < 0 || power < 0);
    }
}