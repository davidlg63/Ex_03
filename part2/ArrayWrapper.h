//
// Created by David on 24/06/2020.
//

#ifndef EX03_ARRAYWRAPPER_H
#define EX03_ARRAYWRAPPER_H
#include <exception>

namespace mtm
{
    template <class T>
    class ArrayWrapper
    {
        T* array;
        int size;

    public:
        ArrayWrapper(int array_size) : array(nullptr), size(array_size)
        {
            try
            {
                array = new T[size];
            }
            catch(const std::bad_alloc& e)
            {
                delete[] array;
                throw e;
            }
        }

        ~ArrayWrapper()
        {
            delete[] array;
        }

        T* getArray() const
        {
            return array;
        }
    };
}
#endif //EX03_ARRAYWRAPPER_H
