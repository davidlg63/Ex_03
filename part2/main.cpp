#include <iostream>
#include "IntMatrix.h"
#include <random>

using mtm::IntMatrix;
using mtm::Dimensions;
using std::cout;

void testConstructor()
{
    Matrix<int> m1 = Matrix<int>(Dimensions(3,3), 5);
    IntMatrix m2 = IntMatrix(Dimensions(10,12), 3491);
    IntMatrix m3 = IntMatrix(Dimensions(3,5));
    IntMatrix m4 = IntMatrix(Dimensions(1,3), 0);
    IntMatrix m5 = IntMatrix(Dimensions(1,1), 1);
    IntMatrix m6 = IntMatrix(Dimensions(7,1), 15);

    cout << m1 << "\n";
    cout << m2 << "\n";
    cout << m3 << "\n";
    cout << m4 << "\n";
    cout << m5 << "\n";
    cout << m6 << "\n";
}

void testCopyConstructorAndAssignment()
{
    IntMatrix m1 = IntMatrix(Dimensions(3,3), 5);
    IntMatrix m2 = IntMatrix(Dimensions(10,12), 3491);
    IntMatrix m3 = m1;
    IntMatrix m4 = m2;

    cout << m3 << "\n";
    cout << m4 << "\n";

    IntMatrix m5 = IntMatrix(Dimensions(1,1), 1);
    IntMatrix m6 = IntMatrix(Dimensions(7,1), 15);

    m3 = m5;
    m4 = m6;

    cout << m3 << "\n";
    cout << m4 << "\n";
}

void testIdentity()
{
    IntMatrix i1 = IntMatrix::Identity(1);
    IntMatrix i2 = IntMatrix::Identity(2);
    IntMatrix i0 = IntMatrix::Identity(0);
    IntMatrix i10 = IntMatrix::Identity(10);

    cout << i1 << "\n";
    cout << i2 << "\n";
    cout << i0 << "\n";
    cout << i10 << "\n";
}

void testQuestionDimensions()
{
    IntMatrix m(Dimensions(3, 7), 2);
    cout << m.height() << "\n" << m.width() << "\n" << m.size() << "\n";
}

void testTranspose()
{
    IntMatrix m(Dimensions(12, 3), 2);
    m = m.transpose();
    cout << m;
}

void testAdditionAndMinus()
{
    IntMatrix m1(Dimensions(5,2));
    IntMatrix m2(Dimensions(5,2));

    for(int i = 0; i < m1.height(); i++)
    {
        for(int j = 0; j < m1.width(); j++)
        {
            int r = rand();
            m1(i,j) = r;
            m2(i,j) = m1(i,j);
        }
    }

    cout << m1 - m2;

    m1 = IntMatrix(Dimensions(2,4), 5);
    cout << 3 + -m1;
}

void testIndexOperator()
{
    IntMatrix m(Dimensions(4,5), 1);
    m(1,0) = 4;
    m(3,2) = 16;
    cout << m(0,3) << "\n" << m(1,0) << "\n" << m;
}

void testLogicOperators()
{
    IntMatrix m1(Dimensions(2,2));
    m1(0,0) = 3;
    m1(0,1) = 0;
    m1(1,0) = -7;
    m1(1,1) = 4;

    cout << (m1 == 3) << (m1 != 0) << (m1 <= 0) << (m1 >= 3) << (m1 < 0) << (m1 > 0);
}

void testAllAny()
{
    IntMatrix m(Dimensions(2,2));
    cout << any(m) << all(m); //both should be false
    m(1,0) = -17;
    cout << any(m) << all(m); //should be true false
    m(0,0) = 3;
    m(0,1) = 99;
    m(1,1) = 6;
    cout << any(m) << all(m); //both true
}

void testIterator()
{
    IntMatrix mat(Dimensions(4, 3));
    int i = 0;
    for(IntMatrix::iterator it = mat.begin(); it != mat.end(); it++)
    {
        *it = i++;
    }
    cout << mat;

    IntMatrix::iterator it2 = mat.begin();
    IntMatrix::iterator it3 = mat.begin();
    for(int i = 0; i < 3; i++){++it2;}
    for(int i = 0; i < 4; i++){it3++;}
    cout << *it2 << "\n";
    cout << *it3 << "\n";
    cout << (it2 == it3) <<"\n"; //false
    it2 = it3;
    IntMatrix::iterator it4 = it3;
    cout << *it2 << "\n";
    cout << *it3 << "\n";
    cout << *it4 << "\n";
    cout << (it2 != it4) << "\n"; //false
    cout << (it3 == it2) << "\n"; //true
    *it4=123;
    cout << *it4;
}

void testConstIterator()
{
    const IntMatrix mat(Dimensions(3,5), 10);
    IntMatrix::const_iterator it = mat.begin();
    IntMatrix::const_iterator it2 = ++mat.begin();
    it2++;
    ++it2;
    it2++;
    it2++;
    ++it2;
    ++it2;
    cout << *it << "\n";
    cout << *it2 << "\n";
    cout << (it != it2) << "\n"; //true
    cout << (*it == *it2) << "\n"; //true
    it2 = it;
    cout << (it2 == it);
}

int main() {
    //elad
    testConstructor();
    testCopyConstructorAndAssignment();
    testIdentity();
    testQuestionDimensions();
    testTranspose();
    testAdditionAndMinus();
    //david:
    testIndexOperator();
    testLogicOperators();
    testAllAny();
    testIterator();
    testConstIterator();
    testApply();
    return 0;
}

