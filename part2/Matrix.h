//
// Created by X on 23/06/2020.
//

#ifndef PART2_MATRIX_H
#define PART2_MATRIX_H

#include "Auxiliaries.h"
#include <exception>
#include <string>
#include "Array.h"

namespace  mtm
{
    template <class T>
    class Matrix
    {
    private:
        Dimensions dimensions;
        T** data;
        void CreateArray( Dimensions dim);
        /*In the SetData function we assume that if the data is a complex datatype than it  has its own
        assigment operator*/
        void SetData(Dimensions dim, T value);
        static bool illegalDimensions(int i, int j, Dimensions dim);

    public:
        Matrix( Dimensions dims, T value );
        /* in the copy c'tor, we will assume that if the matrix contains a complex datatype,
         * than the datatype has its own copy c'tor */
        Matrix(const Matrix&);
        /* in the d'tor, we will assume that if the matrix contains a complex datatype,
         * than the datatype has its own d'tor */
        ~Matrix();
        Matrix<T>Diagonal( int dim,  T value = 0);
        /* In the transpose function we will assume that if the matrix contains a complex datatype,
        * than the datatype has its own copy c'tor */
        Matrix<T> transpose() const;
        /* In the operator+= implementation we will assume that if the matrix contains a complex datatype,
        * than the datatype has its own operator+= */
        Matrix<T>& operator+=(const Matrix<T>& mat1);
        /* In the operator- implementation we will assume that if the matrix contains a complex datatype,
         * than this datatype has its own operator-*/
        Matrix<T>& operator-();
        T& operator()(int i, int j)
        {
            if(!illegalDimensions(i, j, dimensions))
            {
                throw Matrix<T>::AccessIllegalElement();
            }
            return data[i][j];
        }

        const T& operator()(int i, int j) const
        {
            if(!illegalDimensions(i, j, dimensions))
            {
                throw Matrix<T>::AccessIllegalElement();
            }
            return data[i][j];
        }

        int hight() const
         {
             return dimensions.getRow();
         }

        int width() const
         {
             return dimensions.getCol();
         }

        int size() const
         {
            return dimensions.getCol() * dimensions.getCol();
         }
         /* in the following comparision function, We assume that if T is complex datatype, than it has the
          * comparision operator necessary for our code to compile. */
         Matrix<T> operator==( T value) const;
         Matrix<T> operator!=( T value) const;
         Matrix<T> operator<=( T value) const;
         Matrix<T> operator>=(T value) const;
         Matrix<T> operator>( T value) const;
         Matrix<T> operator<( T value) const;
         bool all();
         bool any();
         /* In the next function we will assume that T has its own operator+=*/
         Matrix<T>& operator+=( T value);


        /* in the following friend functions we weill assume that if the matrix contains a complex datatype,
         * than the datatype has its own relevant operator as the function */
        friend Matrix<T> operator+(const Matrix<T>& mat1, const Matrix<T>& mat2);
        friend Matrix<T> operator-(const Matrix<T>& mat1, const Matrix<T>& mat2);
        friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& output_matrix);

        class AccessIllegalElement : std::exception
        {
            public:
            const char* what() const noexcept override
            {
                const char *error_message = "Mtm matrix error: An attempt to access an illegal element";
                return error_message;
            }
        };

        class IllegalInitialization : std::exception
        {
            public:
            const char* what() const noexcept override
            {
                const char *error_message = "Mtm matrix error: Illegal initialization values";
                return error_message;
            }
        };

        class DimensionMismatch : std::exception
        {
            const Matrix<T> first_mat;
            const Matrix<T> second_mat;
        public:
            DimensionMismatch(Matrix<T> mat1, Matrix<T> mat2) : first_mat(mat1), second_mat(mat2)
            {};
            const char* what() const noexcept override
            {
                std::string return_message = "Mtm matrix error: Dimension mismatch: "
                        + this->first_mat.dimensions.toString() + this->second_mat.dimensions.toString();
                const char *error_message = return_message.c_str();
                return error_message;
            }
        };
     };

    template <class T>
    Matrix<T> operator+( T value ,const Matrix<T>& mat1);
    template <class T>
    Matrix<T> operator+(const Matrix<T>& mat1,  T value);



    template<class T>
    Matrix<T>::Matrix(const Dimensions dim, T value) : dimensions(dim)
    {
       if(dim.getCol()<=0 ||dim.getRow()<=0)
       {
           throw Matrix<T>::IllegalInitialization();
       }

       this->CreateArray(dim);
       this->SetData(dim,value);

    }

    template <class T>
    Matrix<T>::Matrix(const Matrix<T>& mat_to_copy): dimensions(mat_to_copy.dimensions)
    {
        this->CreateArray(mat_to_copy.dimensions);
        for (int i=0; i< dimensions.getRow(); i++)
        {
            for (int j=0; j< dimensions.getRow(); j++)
            {
                data[i][j]= mat_to_copy.data[i][j];
            }
        }
    }

    template <class T>
    Matrix<T>::~Matrix()
    {
        for(int i=0; i<dimensions.getRow(); i++)
        {
            delete[] data[i];
        }
        delete[] data;
    }


    template <class T>
    Matrix<T> Matrix<T>::Diagonal(const int dim, const T value)
    {
        if (dim<=0)
        {
            throw Matrix<T>::IllegalInitialization();
        }
        Dimensions dimension= Dimensions(dim,dim);
        Matrix<T> diagonal_Matrix(dimension);
        for (int i=0; i<dim; i++)
        {
            diagonal_Matrix.data[i][i]=value;
        }
        return  diagonal_Matrix;
    }

    template <class T>
    Matrix<T> Matrix<T>::transpose() const
    {
        Dimensions transpose_dim=(this->dimensions.getCol(),this->dimensions.getRow());
        Matrix<T> transpose_mat(transpose_dim);
        for(int i=0; i<dimensions.getRow(); i++)
        {
            for(int j=0; j<dimensions.getCol(); j++)
            {
                transpose_mat.data[j][i]=this->data[i][j];
            }
        }
        return transpose_mat;
    }

    template <class T>
    Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& mat1)
    {
        for(int i=0; i<dimensions.getRow();i++)
        {
            for (int j = 0; j < dimensions.getCol(); j++)
            {
              data[i][j]=mat1(i,j) ;
            }
        }
    }

    template <class T>
    Matrix<T>& Matrix<T>::operator-()
     {
         for(int i=0; i<dimensions.getRow();i++)
         {
             for (int j = 0; j < dimensions.getCol(); j++)
             {
                 data[i][j]=-data[i][j] ;
             }
         }
         return *this;
     }


    template <class T>
    Matrix<T> Matrix<T>::operator==(const T value) const
    {
        Matrix<bool> result_matrix=Matrix<bool>(this->dimensions,false);
        for (int i=0; i<dimensions.getRow(); i++)
        {
            for(int j=0; j<dimensions.getCol();j++)
            {
                if (data[i][j]==value)
                {
                    result_matrix.data[i][j]=true;
                }
            }
        }
        return result_matrix;
    }

    template <class T>
    Matrix<T> Matrix<T>::operator!=(const T value) const
    {
        Matrix<bool> result_matrix=Matrix<bool>(this->dimensions,false);
        for (int i=0; i<dimensions.getRow(); i++)
        {
            for(int j=0; j<dimensions.getCol();j++)
            {
                if (data[i][j]!=value)
                {
                    result_matrix.data[i][j]=true;
                }
            }
        }
        return result_matrix;
    }

    template <class T>
    Matrix<T> Matrix<T>::operator>=(const T value) const
    {
        Matrix<bool> result_matrix=Matrix<bool>(this->dimensions,false);
        for (int i=0; i<dimensions.getRow(); i++)
        {
            for(int j=0; j<dimensions.getCol();j++)
            {
                if (data[i][j]>=value)
                {
                    result_matrix.data[i][j]=true;
                }
            }
        }
        return result_matrix;
    }

    template <class T>
    Matrix<T> Matrix<T>::operator<=(const T value) const
    {
        Matrix<bool> result_matrix=Matrix<bool>(this->dimensions,false);
        for (int i=0; i<dimensions.getRow(); i++)
        {
            for(int j=0; j<dimensions.getCol();j++)
            {
                if (data[i][j]<=value)
                {
                    result_matrix.data[i][j]=true;
                }
            }
        }
        return result_matrix;
    }

    template <class T>
    Matrix<T> Matrix<T>::operator>(const T value) const
    {
        Matrix<bool> result_matrix=Matrix<bool>(this->dimensions,false);
        for (int i=0; i<dimensions.getRow(); i++)
        {
            for(int j=0; j<dimensions.getCol();j++)
            {
                if (data[i][j]>value)
                {
                    result_matrix.data[i][j]=true;
                }
            }
        }
        return result_matrix;
    }

    template <class T>
    Matrix<T> Matrix<T>::operator<(const T value) const
    {
        Matrix<bool> result_matrix=Matrix<bool>(this->dimensions,false);
        for (int i=0; i<dimensions.getRow(); i++)
        {
            for(int j=0; j<dimensions.getCol();j++)
            {
                if (data[i][j]<value)
                {
                    result_matrix.data[i][j]=true;
                }
            }
        }
        return result_matrix;
    }

    template <class T>
    bool Matrix<T>::all()
    {
        for (int i=0; i<dimensions.getRow(); i++)
        {
            for(int j=0; j<dimensions.getCol();j++)
            {
              if (!data[i][j])
              {
                  return false;
              }
            }
        }
        return true;
    }

    template <class T>
    bool Matrix<T>::any()
    {
        for (int i=0; i<dimensions.getRow(); i++)
        {
            for(int j=0; j<dimensions.getCol();j++)
            {
                if (data[i][j])
                {
                    return true;
                }
            }
        }
        return false;
    }


    template <class T>
    Matrix<T>& Matrix<T>::operator+=(const T value)
    {
        for (int i=0; i<dimensions.getRow();i++)
        {
            for(int j=0; j<dimensions.getCol();j++)
            {
                data[i][j]+=value;
            }
        }
        return *this;
    }


    template <class T>
    Matrix<T> operator+(const T value, const Matrix<T>& mat1)
    {
       Matrix<T> tmp_mat=mat1;
       for (int i=0; i<mat1.dimensions.getRow();i++)
       {
           for(int j=0;j<mat1.dimensions.getCol();j++)
           {
               tmp_mat[i][j]= value+tmp_mat[i][j];
           }
       }
        return tmp_mat;
    }



    template <class T>
    Matrix<T> operator+(const Matrix<T>& mat1, const T value)
    {
       return mat1+=value;
    }


    template<class T>
    Matrix<T> operator+(const Matrix<T>& mat1, const Matrix<T>& mat2)
    {
        Matrix<T> tmp= mat1;
        return  tmp+=mat2;
    }

    template<class T>
    Matrix<T> operator-(const Matrix<T>& mat1, const Matrix<T>& mat2)
    {
        Matrix<T> tmp= -mat1;
        return  tmp+=mat2;
    }

    template<class T>
    std::ostream& operator<<(std::ostream& os, const Matrix<T>& output_matrix)
    {

        os=printMatrix(os, Matrix<T>::begin,Matrix<T>::end);
        return os;

    }

    template <class T>
     void  Matrix<T>::CreateArray(const Dimensions dim)
    {

         data = ArrayWrapper<T>(dim.getRow()).array;
        for (int i=0; i<dim.getRow(); i++)
        {
                data[i] = ArrayWrapper<T>(dim.getCol()).array;
        }
    }

    template <class T>
     void Matrix<T>::SetData(Dimensions dim, T value)
    {
        for(int i=0 ;i<dim.getRow(); i++)
        {
            for(int j=0; j<dim.getCol(); j++)
            {
                data[i][j]= value;
            }
        }
    }

    template <class T>
     bool Matrix<T>::illegalDimensions(int i, int j, Dimensions dim)
    {
        int rows=dim.getRow(), col=dim.getCol();
        return !(i < 0 || i > rows || j < 0 || j > col);
    }

}

#endif //PART2_MATRIX_H
