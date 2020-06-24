#include <exception>
#include ".Auxiliaries.h"
#include "Matrix.h"
namespace mtm
{
    template<class T>
    T&  Matrix<T>::iterator::operator*() {
        if (current_row < 0 || current_row >= matrix->dims.getRow() || current_column < 0 || current_column >=
                                                                                             matrix->dims.getCol()) {
            throw AccessIllegalElement();
        }
        return matrix->data[current_row][current_column];
    }

    template<class T>
    typename Matrix<T>::iterator& Matrix<T>::iterator::operator++() {
        if (current_column == matrix->dims.getCol()) {
            current_column = 0;
            current_row++;
        } else {
            current_column++;
        }

        return *this;
    }

    template <class T>
    typename Matrix<T>::iterator Matrix<T>::iterator::operator++(int)
    {
        iterator temp = *this;
        ++*this;
        return temp;
    }
}