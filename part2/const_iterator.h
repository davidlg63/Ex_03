//
// Created by David on 23/06/2020.
//

#ifndef EX03_CONST_ITERATOR_H
#define EX03_CONST_ITERATOR_H

#include <exception>
#include ".Auxiliaries.h"
#include "Matrix.h"

namespace mtm
{
    template<class T>
    const T& Matrix<T>::const_iterator::operator*()
    {
        if (current_row < 0 || current_row >= matrix->dims.getRow() || current_column < 0 || current_column >=
        matrix->dims.getCol())
        {
            throw AccessIllegalElement();
        }
        return matrix->data[current_row][current_column];
    }

    template<class T>
    typename Matrix<T>::const_iterator& Matrix<T>::const_iterator::operator++()
    {
        if (current_column == matrix->dims.getCol())
        {
            current_column = 0;
            current_row++;
        }
        else
        {
            current_column++;
        }

        return *this;
    }

    template <class T>
    typename Matrix<T>::const_iterator Matrix<T>::const_iterator::operator++(int)
    {
        const_iterator temp = *this;
        ++*this;
        return temp;
    }
}
#endif //EX03_CONST_ITERATOR_H
