//
// Created by David on 25/06/2020.
//

#include "Exception.h"


namespace mtm
{
    Exception::Exception(const std::string& error) : error_message(error)
    {}

    const char* Exception::what() const noexcept
    {
        return error_message.c_str();
    }

    GameException::GameException(const std::string& exception_name) :
    Exception("A game related error has occurred: " + exception_name)
    {}

    IllegalArgument::IllegalArgument() : GameException("IllegalArgument")
    {}

    IllegalCell::IllegalCell() : GameException("IllegalCell")
    {}

    CellEmpty::CellEmpty() : GameException("CellEmpty")
    {}

    MoveTooFar::MoveTooFar() : GameException("MoveTooFar")
    {}

    CellOccupied::CellOccupied()  : GameException("CellOccupied")
    {}

    OutOfRange::OutOfRange()  : GameException("OutOfRange")
    {}

    OutOfAmmo::OutOfAmmo()  : GameException("OutOfAmmo")
    {}

    IllegalTarget::IllegalTarget()  : GameException("IllegalTarget")
    {}
}
