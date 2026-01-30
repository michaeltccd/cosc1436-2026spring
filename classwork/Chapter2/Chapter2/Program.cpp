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
}