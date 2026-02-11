/*
 * Chapter 3
 * COSC 1436
 * Spring 2026
 */
#include <iostream>
#include <string>

void main()
{        
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