//
// Created by David on 25/06/2020.
//

#ifndef EX03_EXCEPTION_H
#define EX03_EXCEPTION_H

#include <exception>
#include <string>

namespace mtm
{
    class Exception : std::exception
    {
        protected:
            const std::string error_message;
            Exception(const std::string& error);

    public:
        virtual ~Exception() = default;
        const char* what() const noexcept override;
    };

    class GameException : public Exception
    {
    protected:
        GameException(const std::string& exception_name);

    public:
        virtual ~GameException() = default;
    };

    class IllegalArgument : public GameException
    {
    public:
        IllegalArgument();
    };

    class IllegalCell : public GameException
    {
    public:
        IllegalCell();
    };

    class CellEmpty : public GameException
    {
    public:
        CellEmpty();
    };

    class MoveTooFar : public GameException
    {
    public:
        MoveTooFar();
    };

    class CellOccupied : public GameException
    {
    public:
        CellOccupied();
    };

    class OutOfRange : public GameException
    {
    public:
        OutOfRange();
    };

    class OutOfAmmo : public GameException
    {
    public:
        OutOfAmmo();
    };

    class IllegalTarget : public GameException
    {
    public:
        IllegalTarget();
    };
}
#endif //EX03_EXCEPTION_H
