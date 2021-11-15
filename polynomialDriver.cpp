// ------------------------------------------------ PROG 03 -------------------------------------------------------

// Michael Yu, CSS 501

// Created on: 11/15/2021

// Date of Last Modification: 11/15/2021

// ---------------------------------------------------------------------------------------------------------------

// Purpose - Implement ADT Polynomial class as a linked list

#include "polynomial.h"
#include <iostream>
#include <ios>
#include <iomanip>
#include <sstream>

static int testCount = 0;
static int testPassed = 0;
static int testFailed = 0;

// Unit test template for checking actual against expected
template<typename T>
bool TEST(const T& expected, const T& actual, const std::string filename, const int lineNumber, std::ostream& os)
{
    ++testCount;
    bool pass = expected == actual;
    if (!pass)
    {
        os << "Test failed in \"" << filename << "\", line number " << lineNumber <<
           ". Expected: " << expected << ", Actual: " << actual << std::endl;
        ++testFailed;
    }
    else ++testPassed;
    return pass;
}

// Printing result template for unit test
template<typename T>
void PRINT_TEST(const T& expected, const T& actual, const int printWidth, const std::string testname, const bool test, std::ostream& os)
{
    os << std::left << std::setw(50) << testname <<
              "Expected: " << expected <<
              ", Actual: " << actual << ", pass: " << std::boolalpha << test << std::endl;
}

int main( )
{
    bool test = false;
    std::stringstream ss;

    std::cout << "=== START: TESTING EMPTY POLYNOMIAL ===" << std::endl;
    Polynomial p0;

    test = TEST(0, p0.degree(), __FILE__, __LINE__, ss);
    PRINT_TEST(0, p0.degree(), 5, "Polynomial::degree", test, std::clog);

    test = TEST(0.0, p0.coefficient(10), __FILE__, __LINE__, ss);
    PRINT_TEST(0.0, p0.coefficient(10), 5, "Polynomial::coefficient", test, std::clog);

    std::cout << "p0 (empty) = " << p0 << std::endl;
    std::cout << "=== END: TESTING EMPTY POLYNOMIAL ===" << std::endl;

    std::cout << "=== START: TESTING NON-EMPTY POLYNOMIAL ===" << std::endl;
    Polynomial p1;
    test = TEST(true, p1.changeCoefficient( -1, 2 ), __FILE__, __LINE__, ss);
    PRINT_TEST(true, p1.changeCoefficient( -1, 2 ), 10, "Polynomial::changeCoefficient", test, std::clog);

    test = TEST(false, p1.changeCoefficient( -1, -2 ), __FILE__, __LINE__, ss);
    PRINT_TEST(false, p1.changeCoefficient( -1, -2 ), 10, "Polynomial::changeCoefficient (negative power)", test, std::clog);

    test = TEST(2, p1.degree(), __FILE__, __LINE__, ss);
    PRINT_TEST(2, p1.degree(), 5, "Polynomial::degree", test, std::clog);

    p1.changeCoefficient( -9.8, 0 );
    p1.changeCoefficient( 4, 5 );
    p1.changeCoefficient( 7.2, 3 );

    std::cout << "p1 (initial) = " << p1 << std::endl;

    p1.changeCoefficient( 117.2, 3 );

    test = TEST(117.2, p1.coefficient(3), __FILE__, __LINE__, ss);
    PRINT_TEST(117.2, p1.coefficient(3), 5, "Polynomial::coefficient (change existing coefficient)", test, std::clog);

    p1.changeCoefficient( -1, 1 );
    p1.changeCoefficient( 0, 3 );
    test = TEST(0.0, p1.coefficient(3), __FILE__, __LINE__, ss);
    PRINT_TEST(0.0, p1.coefficient(3), 5, "Polynomial::coefficient (change existing coefficient to 0)", test, std::clog);

    std::stringstream ssPoly;
    ssPoly << p1;
    std::string expectedStr("4x^5 - x^2 - x - 9.8");
    test = TEST(expectedStr, ssPoly.str(), __FILE__, __LINE__, ss);
    PRINT_TEST(expectedStr, ssPoly.str(), 5, "Polynomial::operator<<", test, std::clog);

    test = TEST(5, p1.degree(), __FILE__, __LINE__, ss);
    PRINT_TEST(5, p1.degree(), 5, "Polynomial::degree", test, std::clog);
    std::cout << "p1 (final) = " << p1 << std::endl;
    std::cout << "=== END: TESTING NON-EMPTY POLYNOMIAL ===" << std::endl;

    std::cout << "=== START: TESTING POLYNOMIAL COPY CONSTRUCTOR ===" << std::endl;
    Polynomial p2(p1);
    test = TEST(true, p1 == p2, __FILE__, __LINE__, ss);
    PRINT_TEST(true, p1 == p2, 5, "Polynomial::operator==", test, std::clog);

    p2.changeCoefficient(13, 13);
    test = TEST(true, p1 != p2, __FILE__, __LINE__, ss);
    PRINT_TEST(true, p1 != p2, 5, "Polynomial::operator!=", test, std::clog);

    test = TEST(13, p2.degree(), __FILE__, __LINE__, ss);
    PRINT_TEST(13, p2.degree(), 5, "Polynomial::degree", test, std::clog);

    std::cout << "p1 = " << p1 << std::endl;
    std::cout << "p2 = 13x^13 + p1 = " << p2 << std::endl;

    std::cout << "=== END: TESTING POLYNOMIAL COPY CONSTRUCTOR ===" << std::endl;

    std::cout << "=== START: TESTING POLYNOMIAL ARITHMETIC AND ASSIGNMENT ===" << std::endl;
    Polynomial p3;
    Polynomial p4;

    // p1 = 4x^5 - x^2 - x - 9.8
    // p2 = 13x^13 + 4x^5 - x^2 - x - 9.8
    p3 = p2;
    p4 = p1;

    p4.changeCoefficient(9, 8);

    test = TEST(true, p3 == p2, __FILE__, __LINE__, ss);
    PRINT_TEST(true, p3 == p2, 5, "Polynomial::operator== (via copy assignment)", test, std::clog);

    auto p5 = p3 + p4;
    std::stringstream ssPoly2;
    ssPoly2 << p5;
    expectedStr = "13x^13 + 9x^8 + 8x^5 - 2x^2 - 2x - 19.6";
    test = TEST(expectedStr, ssPoly2.str(), __FILE__, __LINE__, ss);
    PRINT_TEST(expectedStr, ssPoly2.str(), 5, "Polynomial::operator+ (p3 + p4)", test, std::clog);

    Polynomial p6;
    p6.changeCoefficient(8, 5);
    p6.changeCoefficient(-19.6, 0);
    p6.changeCoefficient(-5, 2);
    p6.changeCoefficient(-2, 1);

    p5.changeCoefficient(0, 1);
    p6.changeCoefficient(0, 1);
    auto p7 = p6 - p5;

    std::stringstream ssPoly3;
    ssPoly3 << p7;
    expectedStr = "-13x^13 - 9x^8 - 3x^2";
    test = TEST(expectedStr, ssPoly3.str(), __FILE__, __LINE__, ss);
    PRINT_TEST(expectedStr, ssPoly3.str(), 5, "Polynomial::operator- (p6 - p5)", test, std::clog);

    auto p8 = p1;
    p8.changeCoefficient(8, 8);
    p8.changeCoefficient(-2,11);

    std::cout << "p8 (initial) = p1 + 8x^8 - 2x^11 = " << p8 << std::endl;

    p8 += p2;

    std::stringstream ssPoly4;
    ssPoly4 << p8;
    expectedStr = "13x^13 - 2x^11 + 8x^8 + 8x^5 - 2x^2 - 2x - 19.6";
    test = TEST(expectedStr, ssPoly4.str(), __FILE__, __LINE__, ss);
    PRINT_TEST(expectedStr, ssPoly4.str(), 5, "Polynomial::operator+=", test, std::clog);

    auto p9 = p1;
    p9.changeCoefficient(8, 8);
    p9.changeCoefficient(-2,11);

    std::cout << "p9 (initial) = p1 + 8x^8 - 2x^11 = " << p9 << std::endl;

    p9 -= p2;

    std::stringstream ssPoly5;
    ssPoly5 << p9;
    expectedStr = "-13x^13 - 2x^11 + 8x^8";
    test = TEST(expectedStr, ssPoly5.str(), __FILE__, __LINE__, ss);
    PRINT_TEST(expectedStr, ssPoly5.str(), 5, "Polynomial::operator-=", test, std::clog);

    std::cout << "=== END: TESTING POLYNOMIAL ARITHMETIC AND ASSIGNMENT ===" << std::endl;

    std::clog << ss.str() << std::endl;
    std::cout << "Number of tests: " << testCount << ", Tests passed: " << testPassed << ", Tests failed: " << testFailed << std::endl;
    std::cout << "See output.log file for more information on the tests.\n" << std::endl;

    std::cout << "p1 = " << p1 << std::endl;
    std::cout << "p2 = " << p2 << std::endl;
    std::cout << "p3 = " << p3 << std::endl;
    std::cout << "p4 = " << p4 << std::endl;
    std::cout << "p5 = p3 + p4 = " << p5 << std::endl;
    std::cout << "p6 = " << p6 << std::endl;
    std::cout << "p7 = p5 - p6 = " << p7 << std::endl;
    std::cout << "p8 += p2 = " << p8 << std::endl;
    std::cout << "p9 -= p2 = " << p9 << std::endl;
}

