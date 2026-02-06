/*
 * Chapter 2
 * COSC 1436 Spring 2026
 */
#include <iostream>
#include <string>

// Custom types
struct Point
{
    //Declare the variables that make up the type
    int x;  // Field
    int y;
};

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
    //std::cin >> someVariable;

    int anotherValue = 10, anotherValueAgain = 20;

    //Print out int
    std::cout << someVariable;

    // Arithmetic operators
    //  + - * / % (binary)
    //  + - (unary)

    // integer division problem:: int / int => int
    int quotent = 10 / 3;  // int / int => int

    // modulus - remainder when you divide 2 ints
    int remainder = 10 % 3; //1

    int negativeRemainder = -remainder;
    quotent = +quotent;

    double actualQuotent = 10.0 / 3.0;  // double / double -> double

    //Calculate perimeter of rectangle
    std::cout << "Enter length? ";
    std::cin >> length;

    std::cout << "Enter width? ";
    std::cin >> width;

    // P  = 2L + 2W
    perimeter = length + length + width + width;
    std::cout << "Perimeter = " << perimeter << std::endl;


    // Scope - its lifetime; point of declaration until the block that contains it ends
    //aLocalVariable = 20;
    int aLocalVariable = 0;
    aLocalVariable = 10;

    //Start a new block
    {
        double blockVariableA = 0;

        // Can access var declared in block + any parent blocks
        blockVariableA = 10;
        aLocalVariable = 20;

        // Can redeclare a variable from a parent scope
        //double length;
        length = 80;
    }

    std::cout << length << std::endl;
    //blockVariableA no longer accessible

    // C++ strings
    //  - Not a primitive
    //  - Only usable in C++
    //  - Use = for assignment
    //  - Use + for concatenating 2 string values
    std::string someStringValue;
    someStringValue = "Bob";
    someStringValue = someStringValue + " How are you?";

    // Assignment
    //  - Expression as well
    //  - Value is value of variable after assignment
    //  - Can chain assignment togeth
    length = width = perimeter = 0;

    // Named constants
    //   Literal : 25
    //   Variable : T id = 25;
    // const_decl ::= const T id = E;
    // Casing: Pascal or all uppercase
    // Must be a compile time constant - must be calculatable at compile time
    //  - Literals
    //  - Simple math expressions with constant expressions
    //      4+5, MaximumStudents, MaximumStudents - 10 
    const int MAX_SIZE = 25;
    const int MaximumStudents = 50;

    //Change value at runtime
    //MaximumStudents = 40;  Cannot write to constant

    int largestNumberOfStudents = 25; //Using the literal
    //largestNumberOfStudents = maximumStudents; //Using the variable
    largestNumberOfStudents = MaximumStudents;  // Using constant

    // Create and get input for a point
    Point left;

    std::cout << "Enter the X value: ";
    std::cin >> left.x;

    std::cout << "Enter the Y value: ";
    std::cin >> left.y;

    std::cout << "(" << left.x << ", " << left.y << ")" << std::endl;
}