/*
 * Chapter 3
 * COSC 1436
 * Spring 2026
 */
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

void main()
{   
    // Math functions - cmath
    //  Function | What it does
    //  -----------------------
    //   pow(x, y) | Raises x to y power
    //   sqrt(x)  | Square root of x
    //   abs(x)    | Returns absolute value of x
    //   
    //   ceil(x)   | Smallest possible int that is >= x
    //   floor(x)  | Largest possible int that is <= x
    //
    //   exp(x)    | Exp of X
    //   log(x)    | Log of X  
    //
    //   trunc(x)  | Truncates a floating point value to an int (equivalent to an int typecast)
    //   round(x)  | Rounds a floating point value to an int (cout printing with precision)
    double mathValue;
    std::cout << "Enter value: ";
    std::cin >> mathValue;

    std::cout << std::setw(20) << "Function " << "Result" << std::endl;
    std::cout << std::setw(20) << "pow (square)" << pow(mathValue, 2) << std::endl;
    std::cout << std::setw(20) << "pow (third)" << pow(mathValue, 3) << std::endl;
    std::cout << std::setw(20) << "sqrt" << sqrt(mathValue) << std::endl;
    std::cout << std::setw(20) << "abs" << abs(mathValue) << std::endl;

    std::cout << std::setw(20) << "ceil" << ceil(mathValue) << std::endl;
    std::cout << std::setw(20) << "floor" << floor(mathValue) << std::endl;

    std::cout << std::setw(20) << "exp" << exp(mathValue) << std::endl;
    std::cout << std::setw(20) << "log" << log(mathValue) << std::endl;
    
    std::cout << std::setw(20) << "trunc " << trunc(mathValue) << std::endl;
    std::cout << std::setw(20) << "round " << round(mathValue) << std::endl;
    
    // Prompt for accruded points and total points and determine the average
    int actualPoints, totalPoints;

    std::cout << "Enter the actual points earned: ";
    std::cin >> actualPoints;

    std::cout << "Enter the total points available: ";
    std::cin >> totalPoints;

    // int / int => int, so losing fraction
    // Need to convert one or other to double
    // Options:
    //   1 - Change the type of either variable (wrong answer, variables use type based on values stored)
    //   2 - Type Casting (you explicitly chang the type of an expression)
    //       A :: C++ cast ::= static_cast<T>(E)
    //       B :: C cast ::= (T) E
    double average = (actualPoints / totalPoints) * 100.0; // Wrong 
    average = (static_cast<double>(actualPoints) / totalPoints) * 100;  //Option 2.A
    average = (actualPoints / (double)totalPoints) * 100;  //Option 2.B
    average = ((double)(actualPoints) / totalPoints) * 100;  //Option 2.B

    std::cout << "Average grade = " 
        << std::fixed << std::setprecision(2) 
        << average << std::endl;

    //Formatted output - <iomanip>
    //  Manipulator    Persisted?  What?
    //  --------------------------------
    //  setw(#)        N           Pads the value to the given char length
    //  left           Y           Left justifies values when padded
    //  right          Y           Right justifies values when padded (default)
    //  setfill(char)  Y           Sets character to use when padding values (default is space)
    //  fixed          Y           Forces fixed point notation for floating point values
    //  setprecision(#) Y          Sets precision of numbers
    //                               Precision = total digits when fixed not applied
    //                               Precision = digits to right of decimal when fixed applied
    // 
    // x   y  + - * / %
    // -----------------
    // 3   4  7 -1 12 0 3
    
    double firstValue, secondValue;
    std::cout << "Enter x and y: ";
    std::cin >> firstValue >> secondValue;

    std::cout << std::left << std::fixed;
    std::cout << std::setprecision(3);

    std::cout << std::setw(8) << "x"
        << std::setw(8) << "y"
        << std::setw(10) << "+"
        << std::setw(8) << "-"
        << std::setw(12) << "*"
        << std::setw(10) << "/"
        << std::setw(8) << "%" 
        << std::endl;
    std::cout << std::setfill('-') << std::setw(36) << "" << std::setfill(' ') << std::endl;

    std::cout << std::setw(8) << firstValue 
        << std::setw(8) << secondValue
        << std::setw(10) << (firstValue + secondValue)
        << std::setw(8) << (firstValue - secondValue)
        << std::setw(12) << (firstValue * secondValue)
        << std::setw(10) << (firstValue / secondValue)
        //<< std::setw(4) << (firstValue % secondValue)
        << std::endl;


    // Area of rectangle
    std::cout << "Enter the length: ";

    // std::cin >> E 
    //   Get input from user
    int length;
    std::cin >> length;

    std::cout << "Enter the width: ";

    int width;
    std::cin >> width;

    int area = length * width;
    std::cout << "Area of rectangle = " << area << std::endl;

    // Prompt for name
    std::string name;
    std::cout << "Enter your name: ";

    // HACK to work around getline and cin issues when getline follows cin
    std::cin.ignore(INT32_MAX, '\n');

    //cin with strings will cause issues if string has spaces
    //std::cin >> name;
    std::getline(std::cin, name);

    std::cout << "Hello " << name << std::endl;

    // Area of triangle
    std::cout << "Enter the base and height: ";

    int base, height;
    std::cin >> base >> height;

    // A = 1/2 * b * h
    area = base * height / 2;
    std::cout << "Area of triangle = " << area << std::endl;

    // Combination operators
    //  Op= where op is + - * / %
    //  First operand must be a variable
    base = base + 10;
    base += 10;

    // Type coercion - compiler implicitly coerces one type to another
    //  Applies when using 2 different types in a binary expression
    //  Smaller types are coerced to larger type
    //    double, float, unsigned long, long, unsigned int, int, short/char
    area = (1 / 2) * base * height; // (int / int) * int * int => int
    area = 0.5 * base * height;     // double * int * int => double
    area = (1.0 / 2) * base * height;

    // float + long * int => float
    float someValue = 0.5 * 10;

    // Overflow and underflow
    // When exceeding the range of a type it simply wraps around
    short minValue = -32768;
    short maxValue = 32767;

    maxValue += 1;  //32768 - overflow results in -32768
    minValue -= 1;  //-32769 - underflow results in 32767
}