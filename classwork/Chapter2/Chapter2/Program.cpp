/*
 * Chapter 2
 * COSC 1436 Spring 2026
 */
#include <iostream>

//Entry point of your program
void main()
{
    //What main does
    
    //Display output
    
    // String literals are enclosed in double quotes and represent text
    std::cout << "Hello World" << std::endl;

    std::cout << "Hello " << "World" << std::endl;
    std::cout << "Hello" << " " << "World" << std::endl;    

    // Escape sequence - only usable inside string literals
    //   Start with a slash followed by a special character
    //   \n - newline
    //   \t - horizontal tab
    //   \" - double quote
    //   \\ - slash
    std::cout << "Hello World\n";    
    std::cout << "Hello\tWorld\n";
    std::cout << "Hello \"Bob\", How are you?" << std::endl;
    std::cout << "C:\\Windows\\System32" << std::endl;

    // integer literals - whole numbers
    // 4 + 5 = 9
    std::cout << 4 << " + " << 5 << " = " << 4 + 5 << std::endl;

    // Floating point literal - fractional numbers
    std::cout << 4.5 << " * " << 6.7 << " = " << 4.5 * 6.7 << std::endl;

    // Variable - named memory location where data is stored

    //Prompt user for their name
    std::cout << "Enter your name: ";
    
    //Read user's name
    std::string name;
    std::cin >> name;  //TODO: Talk about this in chapter 3

    //Print out user's name
    std::cout << "Hello " << name << std::endl;

    // variable_decl ::= T id;
    //   id - name of the variable
    //   T - what can be stored in the variable

    // ok: firstname, lastname
    // better: firstName, FirstName
    // worse: first_name, last_name, rest_of_name
    // variable identifiers: camel casing
    //   capitalize on word boundaries, except the first word
    //   eg. payGrade, restOfName    
    
    // Variables must be declared before they can be used
    //   Exists at the point of declaration

    int age;
    double payRate;

    //Compiler error - cannot redeclare a variable
    //double age;

    //Student name
    /*std::string firstName;
    std::string lastName;*/
    std::string firstName, lastName;

    //Perimeter of a rectangle
    /*int length;
    int width;
    int perimeter;
    */
    int length, width, perimeter;    

    // Write to a variable using the assignment operator
    length = 10;
    width = 20;

    std::cout << length;

    // Type
    //   primitives : understood by language
    // Type     Size (Bytes)    Range
    // ------------------------------
    // Signed Integrals
    // --
    // short     2              +-32K (-32768 to 32767)
    // int       4              +-2 billion (default for whole numbers and literals) 
    // long      4              +-2 billion 
    // Unsigned Integrals (reference purposes only)
    // --
    // unsigned short     2              0 to 64K
    // unsigned int       4              0 to 4 billion
    // unsigned long      4              0 to 4 billion
    // Floating point
    // --
    // float     4              e+-38,  5-7 precision
    // double    8              e+-308, 12-15 precision (default for fractional values)
    // Other
    // --
    // bool      1              false, true
    // char      1              -128 to 127 (single character) (default for char literal)

    int hoursWorked; //hours worked in past week
    hoursWorked = 25;

    //Store class average on a quiz
    double classAverage;  // or classQuizAverage
    classAverage = 78.9;

    //Store letter grade for a student
    char letterGrade;
    letterGrade = 'A';

    //Store first time in college
    bool firstTimeInCollege;
    firstTimeInCollege = true;

    // Assignment ::= E = E
    //    l-value = r-value; only variables are l-values
    length = 50;
    width = length;

    // Zero-init variables before use
    // Cannot read variable before definitely assigned
    // Definitely assigned
    //   Assignment
    //   std::cin
    int someVariable = 0;
    //int someVariable; someVariable = 0;

    // Read an int from user
    std::cin >> someVariable;

    int anotherValue = 10, anotherValueAgain = 20;

    //Print out int
    std::cout << someVariable;

}