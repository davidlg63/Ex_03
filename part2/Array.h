//
// Created by X on 23/06/2020.
//

#ifndef PART2_ARRAY_H
#define PART2_ARRAY_H

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
     };
}


#endif //PART2_ARRAY_H
