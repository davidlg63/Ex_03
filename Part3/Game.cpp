//
// Created by David on 25/06/2020.
//

#include "Game.h"
#include "Auxiliaries.h"
#include "Exceptions.h"
#include "Character.h"
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"
#include "Matrix.h"

using std::shared_ptr;
using mtm::Character;
using const_iterator = mtm::Matrix<shared_ptr<Character>>::const_iterator;
using iterator = mtm::Matrix<shared_ptr<Character>>::iterator;
namespace mtm
{
    Game::Game(int height, int width) : board((height > 0 && width > 0) ?
    (Matrix<shared_ptr<Character>>(Dimensions(height, width), nullptr)) : throw IllegalArgument()),
    cpp_counter(0), python_counter(0)
    {}

    Game::Game(const mtm::Game &other) :
    board(Dimensions(other.board.height(), other.board.width()), nullptr), cpp_counter(other.cpp_counter),
    python_counter(other.python_counter)
    {
        try
        {
            for(int i = 0; i < board.height(); i++)
            {
                for(int j = 0; j < board.width(); j++)
                {
                    shared_ptr<Character> to_copy = other.board(i,j);
                    shared_ptr<Character> data_copy = (to_copy == nullptr) ? nullptr : (to_copy->clone());
                    this->board(i,j) = data_copy;
                }
            }
        }
        catch(std::bad_alloc& memory_error)
        {
            std::cout << memory_error.what();
        }
        this->cpp_counter = other.cpp_counter;
        this->python_counter = other.python_counter;
    }

    Game& Game::operator=(const Game& other)
    {
        if(this == &other)
        {
            return *this;
        }

        Game temp(other.board.height(), other.board.width());
        try
        {
            for(int i = 0; i < other.board.height(); i++)
            {
                for(int j = 0; j < other.board.width(); j++)
                {
                    shared_ptr<Character> to_copy = other.board(i,j);
                    shared_ptr<Character> data_copy = (to_copy == nullptr) ? nullptr : (to_copy->clone());
                    temp.board(i,j) = data_copy;
                }
            }
        }
        catch(std::bad_alloc& memory_error)
        {
            std::cout << memory_error.what();
            return *this;
        }

        this->board = temp.board;
        this->cpp_counter = temp.cpp_counter;
        this->python_counter = temp.python_counter;
        return *this;
    }
    

    std::shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team,
                                                    units_t health, units_t ammo, units_t range, units_t power)
    {
        if(isIllegalInitialization(health, ammo, range, power))
        {
            throw IllegalArgument();
        }

        switch(type)
        {
            case SOLDIER:
                return shared_ptr<Character>(new Soldier(team, health, ammo, range, power));

            case MEDIC:
                return shared_ptr<Character>(new Medic(team, health, ammo, range, power));

            case SNIPER:
                return shared_ptr<Character>(new Sniper(team, health, ammo, range, power));
        }
        return nullptr; //should not reach this point.
    }
    
    void Game::attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
    {
        if(!(isInBoard(src_coordinates)) || !(isInBoard(dst_coordinates)))
        {
            throw IllegalCell();
        }

        if(isCellEmpty(src_coordinates))
        {
            throw CellEmpty();
        }

        if(!(board(src_coordinates.row,src_coordinates.col)->isInRange(src_coordinates, dst_coordinates)))
        {
            throw OutOfRange();
        }
        shared_ptr<Character> attacker = board(src_coordinates.row, src_coordinates.col);
        shared_ptr<Character> target = board(dst_coordinates.row, dst_coordinates.col);

        if(attacker->isOutOfAmmo())
        {
            throw OutOfAmmo();
        }
        
        attacker->attack(src_coordinates, dst_coordinates, board, cpp_counter, python_counter);
    }

    std::ostream& operator<<(std::ostream& os, const Game& game)
    {
        const std::string game_string = game.toCharArray();
        const char* output = game_string.c_str();
        return printGameBoard(os, output, output + game.board.size(), game.board.width());
    }

    void Game::addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character) {

        if(!isInBoard(coordinates))
        {
            throw IllegalCell();
        }
        if (!isCellEmpty(coordinates))
        {
            throw CellOccupied();
        }

        this->board(coordinates.row, coordinates.col) = character;
        (character->askTeam() == CPP) ? cpp_counter++ : python_counter++;
    }

    void Game::move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
    {
        if (!isInBoard(src_coordinates) || !isInBoard(dst_coordinates))
        {
            throw IllegalCell();
        }
        if (isCellEmpty(src_coordinates))
        {
            throw CellEmpty();
        }
        if (!(board(src_coordinates.row,src_coordinates.col)->isStepLegal(src_coordinates,dst_coordinates)))
        {
            throw MoveTooFar();
        }
        if (!isCellEmpty(dst_coordinates))
        {
            throw CellOccupied();
        }

        board(dst_coordinates.row,dst_coordinates.col)=board(src_coordinates.row,src_coordinates.col);
        board(src_coordinates.row,src_coordinates.col)= nullptr;
    }

    void Game::reload(const GridPoint & coordinates)
    {
        if (!isInBoard(coordinates))
        {
            throw IllegalCell();
        }
        if (isCellEmpty(coordinates))
        {
            throw CellEmpty();
        }
        board(coordinates.row,coordinates.col)->reload();
    }

    bool Game::isOver(Team* winningTeam) const
    {
        if (winningTeam != nullptr)
        {
            if (cpp_counter == 0 && python_counter != 0) {
                *winningTeam = PYTHON;
                return true;
            } else if ((cpp_counter != 0 && python_counter == 0)) {
                *winningTeam = CPP;
                return true;
            }
            return false;
        }
        return ((cpp_counter == 0 && python_counter != 0) || (cpp_counter != 0  && python_counter == 0));
    }

    //private help methods
    bool Game::isInBoard(const GridPoint& coordinate) const
    {
        return (coordinate.row < board.height() && coordinate.row >= 0
        && coordinate.col < board.width() && coordinate.col >= 0);
    }

    bool Game::isCellEmpty(const GridPoint& coordinate) const
    {
        shared_ptr<Character> character = board(coordinate.row, coordinate.col);
        return (character == nullptr);
    }

    const std::string Game::toCharArray() const
    {
        std::string result;
        for(const_iterator cell = board.begin(); cell != board.end(); cell++)
        {
            result += (*cell == nullptr) ? ' ' : (*cell)->toChar();
        }
        return result;
    }

    bool isIllegalInitialization(units_t health, units_t ammo, units_t range, units_t power)
    {
        return (health <= 0 || ammo<0 || range < 0 || power < 0);
    }
}