//
// Created by David on 24/06/2020.
//

#ifndef EX03_MATRIX_H
#define EX03_MATRIX_H
#include ".Auxiliaries.h"
#include <exception>
#include <string>

namespace  mtm
{
    template <class T>
    class Matrix
    {
    private:
        Dimensions dimensions;
        T** data;
        void CreateArray();
        /*In the SetData function we assume that if the data is a complex datatype than it  has its own
        assigment operator*/
        void SetData(T value);
        static bool illegalDimensions(int i, int j, Dimensions dim);
        void deleteMatrix(T** matrix, int number_of_initialized_columns);
    public:

        Matrix(Dimensions dims, T value = T());
        /* in the copy c'tor, we will assume that if the matrix contains a complex datatype,
         * than the datatype has its own copy c'tor */
        Matrix(const Matrix&);
        /* in the d'tor, we will assume that if the matrix contains a complex datatype,
         * than the datatype has its own d'tor */
        ~Matrix();
        static Matrix<T> Diagonal( int dimensions,  T value = T());
        /* In the transpose function we will assume that if the matrix contains a complex datatype,
        * than the datatype has its own copy c'tor */
        Matrix<T> transpose() const;
        /* In the operator+= implementation we will assume that if the matrix contains a complex datatype,
        * than the datatype has its own operator+= */
        Matrix<T>& operator+=(const Matrix<T>& mat1);
        /* In the operator- implementation we will assume that if the matrix contains a complex datatype,
         * than this datatype has its own operator-*/
        Matrix<T> operator-() const;
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

        int height() const
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
        Matrix<bool> operator==(T value) const;
        Matrix<bool> operator!=(T value) const;
        Matrix<bool> operator<=(T value) const;
        Matrix<bool> operator>=(T value) const;
        Matrix<bool> operator>(T value) const;
        Matrix<bool> operator<(T value) const;
        static bool all(Matrix<T>&);
        static bool any(Matrix<T>&);
        /* In the next function we will assume that T has its own operator+=*/
        Matrix<T>& operator+=(T value);


        /* in the following friend functions we weill assume that if the matrix contains a complex datatype,
         * than the datatype has its own relevant operator as the function */

        template <class Operation>
        Matrix apply(Operation o) const; /*Assumption: o is an object which implements operator() and accepts a
            generic parameter T + returns a T.*/

        class iterator
        {

            const Matrix<T> *matrix;
            int current_row;
            int current_column;

            iterator(const Matrix<T> *matrix, int row, int column) : matrix(matrix), current_row(row), current_column
            (column)
            {};

            friend class Matrix<T>;

        public:
            iterator(const iterator &) = default;

            iterator &operator=(const iterator &) = default;

            ~iterator() = default;

            T &operator*();

            iterator &operator++();

            iterator operator++(int);

            bool operator==(const iterator &it) const
            {
                return (current_row == it.current_row && current_column == it.current_column);
            }

            bool operator!=(const iterator &it) const
            {
                return !(*this == it);
            }

        };

        class const_iterator
        {
            const Matrix<T> *matrix;
            int current_row;
            int current_column;

            const_iterator(const Matrix<T> *matrix, int row, int column) : matrix(matrix), current_row(row),
            current_column(column)
            {};

            friend class Matrix<T>;

        public:
            const_iterator(const const_iterator&) = default;

            const_iterator &operator=(const const_iterator &) = default;

            ~const_iterator() = default;

            const T &operator*();

            const_iterator &operator++();

            const_iterator operator++(int);

            bool operator==(const const_iterator &it) const
            {
                return (current_row == it.current_row && current_column == it.current_column);
            }

            bool operator!=(const const_iterator &it) const
            {
                return !(*this == it);
            }

        };

        iterator begin()
        {
            return typename Matrix<T>::iterator::iterator(this, 0, 0);
        }
        iterator end()
        {
            return typename Matrix<T>::iterator::iterator(this, dimensions.getRow(), 0);
        }
        const_iterator begin() const
        {
            return typename Matrix<T>::const_iterator::const_iterator(this, 0, 0);
        }
        const_iterator end() const
        {
            return typename Matrix<T>::const_iterator::const_iterator(this, dimensions.getRow(),
                    0);
        }

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
            DimensionMismatch(const Matrix<T> mat1, const Matrix<T> mat2) : first_mat(mat1), second_mat(mat2)
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
    static Matrix<T> operator+( T value ,const Matrix<T>& mat1);
    template <class T>
    static Matrix<T> operator+(const Matrix<T>& mat1,  T value);

    template<class T>
    Matrix<T>::Matrix(const Dimensions dim, T value) : dimensions(dim)
    {
        if(dim.getCol()<=0 ||dim.getRow()<=0)
        {
            throw Matrix<T>::IllegalInitialization();
        }

        this->CreateArray();
        this->SetData(value);

    }

    template <class T>
    Matrix<T>::Matrix(const Matrix<T>& mat_to_copy): dimensions(mat_to_copy.dimensions)
    {
        this->CreateArray();
        for (int i=0; i< dimensions.getRow(); i++)
        {
            for (int j=0; j< dimensions.getRow(); j++)
            {
                std::cout<<mat_to_copy.data[i][j]<<std::endl;
                data[i][j]= mat_to_copy.data[i][j];
                std::cout<<data[i][j]<<std::endl<<"\n";
            }
        }
    }

    template <class T>
    Matrix<T>::~Matrix()
    {
        for(int i = 0; i < dimensions.getRow(); i++)
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
        Dimensions transpose_dim(this->dimensions.getCol(), this->dimensions.getRow());
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
        return *this;
    }

    template <class T>
    Matrix<T> Matrix<T>::operator-() const
    {
        Matrix<T> result = *this;
        for(int i=0; i< dimensions.getRow() ;i++)
        {
            for (int j = 0; j < dimensions.getCol(); j++)
            {
                result(i,j) = -data[i][j] ;
            }
        }
        return result;
    }


    template <class T>
    Matrix<bool> Matrix<T>::operator==(const T value) const
    {
        Matrix<bool> result_matrix=Matrix<bool>(this->dimensions,false);
        for (int i=0; i<dimensions.getRow(); i++)
        {
            for(int j=0; j<dimensions.getCol();j++)
            {
                if (data[i][j]==value)
                {
                    result_matrix(i,j) = true;
                }
            }
        }
        return result_matrix;
    }

    template <class T>
    Matrix<bool> Matrix<T>::operator!=(const T value) const
    {
        Matrix<bool> result_matrix=Matrix<bool>(this->dimensions,false);
        for (int i=0; i<dimensions.getRow(); i++)
        {
            for(int j=0; j<dimensions.getCol();j++)
            {
                if (data[i][j]!=value)
                {
                    result_matrix(i,j) = true;
                }
            }
        }
        return result_matrix;
    }

    template <class T>
    Matrix<bool> Matrix<T>::operator>=(const T value) const
    {
        Matrix<bool> result_matrix=Matrix<bool>(this->dimensions,false);
        for (int i=0; i<dimensions.getRow(); i++)
        {
            for(int j=0; j<dimensions.getCol();j++)
            {
                if (data[i][j]>=value)
                {
                    result_matrix(i,j) = true;
                }
            }
        }
        return result_matrix;
    }

    template <class T>
    Matrix<bool> Matrix<T>::operator<=(const T value) const
    {
        Matrix<bool> result_matrix=Matrix<bool>(this->dimensions,false);
        for (int i=0; i<dimensions.getRow(); i++)
        {
            for(int j=0; j<dimensions.getCol();j++)
            {
                if (data[i][j]<=value)
                {
                    result_matrix(i,j) = true;
                }
            }
        }
        return result_matrix;
    }

    template <class T>
    Matrix<bool> Matrix<T>::operator>(const T value) const
    {
        Matrix<bool> result_matrix=Matrix<bool>(this->dimensions,false);
        for (int i=0; i<dimensions.getRow(); i++)
        {
            for(int j=0; j<dimensions.getCol();j++)
            {
                if (data[i][j]>value)
                {
                    result_matrix(i,j) = true;
                }
            }
        }
        return result_matrix;
    }

    template <class T>
    Matrix<bool> Matrix<T>::operator<(const T value) const
    {
        Matrix<bool> result_matrix=Matrix<bool>(this->dimensions,false);
        for (int i=0; i<dimensions.getRow(); i++)
        {
            for(int j=0; j<dimensions.getCol();j++)
            {
                if (data[i][j]<value)
                {
                    result_matrix(i,j) = true;
                }
            }
        }
        return result_matrix;
    }

    template <class T>
    bool Matrix<T>::all(Matrix<T>& matrix)
    {
        for (int i=0; i<matrix.height(); i++)
        {
            for(int j=0; j < matrix.width();j++)
            {
                if (!matrix(i,j))
                {
                    return false;
                }
            }
        }
        return true;
    }

    template <class T>
    bool Matrix<T>::any(Matrix<T>& matrix)
    {
        for (int i=0; i<matrix.height(); i++)
        {
            for(int j=0; j < matrix.width();j++)
            {
                if (matrix(i,j))
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
        Matrix<T> tmp_mat = mat1;
        for (int i=0; i<mat1.height();i++)
        {
            for(int j=0;j<mat1.width();j++)
            {
                tmp_mat(i,j) = value + tmp_mat(i,j);
            }
        }
        return tmp_mat;
    }



    template <class T>
    Matrix<T> operator+(const Matrix<T>& mat1, const T value)
    {
        Matrix<T> temp = mat1;
        return temp += value;
    }


    template<class T>
    Matrix<T> operator+(const Matrix<T>& mat1, const Matrix<T>& mat2)
    {
        if(mat1.height()!=mat2.height() || mat1.width() != mat2.width())
        {
            throw typename Matrix<T>::DimensionMismatch(mat1,mat2);
        }
        Matrix<T> tmp= mat1;
        return  tmp+=mat2;
    }

    template<class T>
    Matrix<T> operator-(const Matrix<T>& mat1, const Matrix<T>& mat2)
    {
        if(mat1.height() != mat2.height() || mat1.width() != mat2.width())
        {
            throw typename Matrix<T>::DimensionMismatch(mat1 , mat2);
        }
        Matrix<T> tmp = -mat1;
        return  tmp+=mat2;
    }

    template<class T>
    std::ostream& operator<<(std::ostream& os, const Matrix<T>& output_matrix)
    {
        std::ostream& output = printMatrix(os, output_matrix.begin(), output_matrix.end(), output_matrix.width());
        return output;
    }

    template <class T>
    void  Matrix<T>::CreateArray()
    {
        data = new T*[dimensions.getRow()];
        int counter = 0;
        for (int i=0; i < dimensions.getRow(); i++)
        {
            try
            {
                data[i] = new T[dimensions.getCol()];
            }

            catch (std::bad_alloc& memory_error)
            {
                deleteMatrix(data, counter);
                throw memory_error;
            }

            counter++;
        }
    }

    template <class T>
    void Matrix<T>::SetData(T value)
    {
        for(int i=0 ;i < dimensions.getRow(); i++)
        {
            for(int j=0; j < dimensions.getCol(); j++)
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

    template <class T>
    template <typename Operation>
    Matrix<T> Matrix<T>::apply(Operation op) const
    {
        Matrix<T> result = *this;
        for(int i = 0; i < dimensions.getRow(); i++)
        {
            for(int j = 0; j < dimensions.getCol(); j++)
            {
                op(result(i,j));
                //result(i,j) = op(data(i,j));
            }
        }
        return result;
    }

    //iterator Methods start here:
    //.......................................................................................................
    template<class T>
    T&  Matrix<T>::iterator::operator*() {
        if (current_row < 0 || current_row >= matrix->dimensions.getRow() ||
        current_column < 0 || current_column >= matrix->dimensions.getCol()) {
            throw AccessIllegalElement();
        }
        return matrix->data[current_row][current_column];
    }

    template<class T>
    typename Matrix<T>::iterator& Matrix<T>::iterator::operator++() {
        if (current_column == matrix->dimensions.getCol() - 1) {
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

    //const_iterator Methods start here:
    //..........................................................................................................
    template<class T>
    const T& Matrix<T>::const_iterator::operator*()
    {
        if (current_row < 0 || current_row >= matrix->dimensions.getRow() ||
        current_column < 0 ||current_column >=matrix->dimensions.getCol())
        {
            throw AccessIllegalElement();
        }
        return matrix->data[current_row][current_column];
    }

    template<class T>
    typename Matrix<T>::const_iterator& Matrix<T>::const_iterator::operator++()
    {
        if (current_column == matrix->dimensions.getCol() - 1)
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

    template <class T>
    void Matrix<T>::deleteMatrix(T** matrix, int number_of_initialized_columns)
    {
        for(int i = number_of_initialized_columns; i > 0; i--)
        {
            delete[] matrix[i - 1];
        }
        delete[] matrix;
    }
}
#endif //EX03_MATRIX_H
