#include <iostream>
#include "Matrix.h"
#include <string>
#include <complex>
#include <vector>

using mtm::Matrix;
using mtm::Dimensions;
using std::cout;
using std::string;
using mtm::Dimensions;

class DivideByTwo
{
public:
    bool operator()(int num) const
    {
        return num / 2;
    }
};

void testConstructor()
{
    const  Matrix<int> m1 = mtm::Matrix<int>(Dimensions(3,3),2 );
    Matrix<float >m2 = mtm::Matrix<float> (Dimensions(10,12), 3491.0f);
    Matrix<double> m3 = mtm::Matrix<double> (Dimensions(3,5),4.2);
    const Matrix<std::string> m4 = mtm::Matrix<std::string>(Dimensions(1,3),"const");
    Matrix<std::string> m5 = mtm::Matrix<std::string>(Dimensions(1,1), "hamburger");
    try
    {
        Matrix<float> m6 = mtm::Matrix<float>(Dimensions(7,-1),15);
    }
    catch (Matrix<float>::IllegalInitialization& e)
    {
        cout<< e.what()<<"\n";
    }
    cout << m1 << "\n";
    cout << m2 << "\n";
    cout << m3 << "\n";
    cout << m4 << "\n";
    cout << m5 << "\n";
}

void testCopyConstructorAndAssignment()
{
    Matrix<int> m1 = Matrix<int>(Dimensions(3,3), 5);
    Matrix<float> m2 = Matrix<float>(Dimensions(10,12), 122.54f);
    Matrix<int> m3= Matrix<int>(Dimensions(2,2));
    cout<< m3<<"\n";
    m3 = m1;
    Matrix<float> m4 = m2;
    m4(0,0) = 0;
    Matrix<std::string> m5 = mtm::Matrix<std::string>(Dimensions(2,2), "hamburger");
    /*try
    {
        Matrix<float> m6 = mtm::Matrix<float>(Dimensions(0, 2), 3.4f);
    }
    catch(const Matrix<float>::IllegalInitialization & e)
    {
        cout<< e.what()<< "\n";
    }*/
    Matrix<std::string> m_string = Matrix<std::string>(Dimensions(2,12),"hamburger");

    cout << m_string << "\n";
    m_string = m5;
    //cout << m3 << "\n";
    //cout << m4 << "\n";
    //cout << m_string << "\n";

}

void testIdentity()
{
    Matrix<int> i1 = Matrix<int>::Diagonal(2,3);
    Matrix<std::string> i2 = Matrix<std::string>::Diagonal(5,"cs");
    Matrix<float> i0 = Matrix<float>::Diagonal(4,0.9f);
    Matrix<short> i10 = Matrix<short>::Diagonal(3);

    cout << i1 << "\n";
    cout << i2 << "\n";
    cout << i0 << "\n";
    cout << i10 << "\n";
}

void testQuestionDimensions()
{
    Matrix<int> m(Dimensions(3, 7), 2);
    cout << m.height() << "\n" << m.width() << "\n" << m.size() << "\n";
}

void testTranspose()
{
    Matrix<int> m(Dimensions(12, 3), 2);
    m = m.transpose();
    cout << m<< "\n";

    Matrix<std::string> m2(Dimensions(4, 7), "I want binary pass at Infi2!!");
    m2 = m2.transpose();
    cout << m2<< "\n";

    Matrix<double> m3(Dimensions(2, 2), 22);
    m3 = m3.transpose();
    cout << m3<< "\n";
}

void testAdditionAndMinus()
{
    Matrix<double> m1(Dimensions(5,2),23.44);
    Matrix<double> m2(Dimensions(5,2),657);

    cout << m1 - m2<< "\n";

    m1 = Matrix<double>(Dimensions(2,4), 5);
    cout << 3.7 + -m1<< "\n";
    cout << m1 + -23.4<< "\n";

    Matrix<std::string> m_str1(Dimensions(2,2),"I have a dream ");
    Matrix<std::string> m_str2(Dimensions(2,2),"And his name is John Seana!!");
    std::string s2="wow amazing";
    std::string s1= ":";
    cout<< (m_str1+=s1) << (s2+m_str2) << "\n";
    cout << m_str1 + m_str2<<"\n";

    Matrix<double> m22(Dimensions(2,2),23.44);
    Matrix<double> m52(Dimensions(5,2),657);

    try
    {
        cout << m52 - m22<<"\n";
    }
    catch (Matrix<double>::DimensionMismatch &e)
    {
        cout << e.what()<< "\n";
    }

}

void testIndexOperator()
{
    Matrix<int> m(Dimensions(4,5), 1);
    m(1,0) = 4;
    m(3,2) = 16;
    cout << m(0,3) << "\n" << m(1,0) << "\n" << m;

    Matrix<float> m_d(Dimensions(4,5));
    m_d(1,0) = 4.7f;
    m_d(3,2) = 16.3f;
    cout << m_d(0,3) << "\n" << m_d(1,0) << "\n";

    Matrix<char*> m_c(Dimensions(4,5), (char*)"@");
    m_c(1,0) = (char*)"#";
    m_c(3,2) = (char*)"$";
    cout << m_c(0,3) << "\n" << m_c(1,0) << "\n" << m_c;
}

void testLogicOperators()
{
    Matrix<int> m1(Dimensions(2,2));
    m1(0,0) = 3;
    m1(0,1) = 0;
    m1(1,0) = -7;
    m1(1,1) = 4;

    cout << (m1 == 3) << (m1 != 0) << (m1 <= 0) << (m1 >= 3) << (m1 < 0) << (m1 > 0);

    Matrix<std::complex<double>> m2(Dimensions(2,2), std::complex<double>(3.5, 0.1));
    m1(0,0) = 3;
    m1(0,1) = 0;
    m1(1,0) = -7;
    m1(1,1) = 4;

    cout << (m2 == std::complex<double>(3,0)) << (m2 != std::complex<double>(0.5, 0.8)) << "\n";
}

void testAllAny()
{
    Matrix<int> m(Dimensions(2,2));
    cout << Matrix<int>::any(m) << Matrix<int>::all(m); //both should be false
    m(1,0) = -17;
    cout << Matrix<int>::any(m) << Matrix<int>::all(m); //should be true false
    m(0,0) = 3;
    m(0,1) = 99;
    m(1,1) = 6;
    cout << Matrix<int>::any(m) << Matrix<int>::all(m); //both true

    Matrix<bool> m2(Dimensions(2,2));
    cout << Matrix<bool>::any(m2) << Matrix<bool>::all(m2); //both should be false
    m(1,0) = true;
    cout << Matrix<bool>::any(m2) << Matrix<bool>::all; //should be true false
    m(0,0) = true;
    m(0,1) = true;
    m(1,1) = 5;
    cout << Matrix<bool>::any(m2) << Matrix<bool>::all(m2); //both true
}

void testIterator()
{
    //Int Matix:
    Matrix<int> mat(Dimensions(4, 3));
    int i = 0;
    for(Matrix<int>::iterator it = mat.begin(); it != mat.end(); it++)
    {
        *it = i++;
    }
    cout << mat;

    Matrix<int>::iterator it2 = mat.begin();
    Matrix<int>::iterator it3 = mat.begin();
    for(int i = 0; i < 3; i++){++it2;}
    for(int i = 0; i < 4; i++){it3++;}
    cout << *it2 << "\n";
    cout << *it3 << "\n";
    cout << (it2 == it3) <<"\n"; //false
    it2 = it3;
    Matrix<int>::iterator it4 = it3;
    cout << *it2 << "\n";
    cout << *it3 << "\n";
    cout << *it4 << "\n";
    cout << (it2 != it4) << "\n"; //false
    cout << (it3 == it2) << "\n"; //true
    *it4=123;
    cout << *it4;

    //double Matix:
    Matrix<double> mat_d(Dimensions(4, 3), 5.7);
    int j = 0;
    for(Matrix<double>::iterator it = mat_d.begin(); it != mat_d.end(); it++)
    {
        *it = j++;
    }
    cout << mat;

    Matrix<double>::iterator it_d2 = mat_d.begin();
    Matrix<double>::iterator it_d3 = mat_d.begin();
    for(int i = 0; i < 3; i++){++it2;}
    for(int i = 0; i < 4; i++){it3++;}
    cout << *it_d2 << "\n";
    cout << *it_d3 << "\n";
    cout << (it_d2 == it_d3) <<"\n"; //false
    it_d2 = it_d3;
    Matrix<double>::iterator it_d4 = it_d3;
    cout << *it_d2 << "\n";
    cout << *it_d3 << "\n";
    cout << *it_d4 << "\n";
    cout << (it_d2 != it_d4) << "\n"; //false
    cout << (it_d3 == it_d2) << "\n"; //true
    *it_d4=123.9;
    cout << *it_d4;

    //string Matix:
    Matrix<string> mat_s(Dimensions(4, 3), "test");
    int k = 0;
    for(Matrix<string>::iterator it_s = mat_s.begin(); it_s != mat_s.end(); it_s++)
    {
        *it_s += std::to_string(k);
    }
    cout << mat;

    Matrix<string>::iterator it_s2 = mat_s.begin();
    Matrix<string>::iterator it_s3 = mat_s.begin();
    for(int i = 0; i < 3; i++){++it_s2;}
    for(int i = 0; i < 4; i++){it_s3++;}
    cout << *it_s2 << "\n";
    cout << *it_s3 << "\n";
    cout << (it_s2 == it_s3) <<"\n"; //false
    it_s2 = it_s3;
    Matrix<string>::iterator it_s4 = it_s3;
    cout << *it_s2 << "\n";
    cout << *it_s3 << "\n";
    cout << *it_s4 << "\n";
    cout << (it_s2 != it_s4) << "\n"; //false
    cout << (it_s3 == it_s2) << "\n"; //true
    *it_s4="123";
    cout << *it_s4;


}

void testConstIterator()
{
    //int matrix:
    const Matrix<string> mat(Dimensions(3,5), "test");
    Matrix<string>::const_iterator it = mat.begin();
    Matrix<string>::const_iterator it2 = ++mat.begin();
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

int multiplyByTwo(int num)
{
    return num * 2;
}
void testApply()
{
    int (*func_pointer)(int) = &multiplyByTwo;

    Matrix<int> diagonal2 = Matrix<int>::Diagonal(3, 3);
    cout << diagonal2.apply(func_pointer) << "\n";
    cout << diagonal2.apply(DivideByTwo()) << "\n";
}

int main() {
    //elad
    //testConstructor();
    testCopyConstructorAndAssignment();
    /*testIdentity();
    testQuestionDimensions();
    testTranspose();
    testAdditionAndMinus();
    //david:
    testIndexOperator();
    testLogicOperators();
    testAllAny();
    testIterator();
    testConstIterator();
    testApply();*/
    return 0;
}

