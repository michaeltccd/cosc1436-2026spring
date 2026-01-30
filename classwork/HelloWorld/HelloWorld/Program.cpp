/*
 * File header
 * Name
 * Lab #
 * COSC 1436 Spring 2026
 */
#include <iostream>

// token - word in a program
//   keyword - Word that has special meaning to the language
//   identifier - Word that has special meaning to you 
//   punctuators - () {} + - 
// comments - Annotations about the code, compiler ignores them  
// pre-processor directives - Removed before compilation, always start with #

// Two approaches to comments
// Single line -> // ... (eol)
// Multi line -> /* ... */

/* This is a multi line comment
 * Continuing the comments
 * Yet more comments
 */

/* This is a multi line comment
 Continuing the comments
 Yet more comments
 */

// Some rules
// - Case sensitive
// - Keywords are lower case
// - Whitespace doesn't matter except between 2 tokens
// - Code runs top down
// - Source lines not equal to executable code in all cases
void main()
{
    // Indent once each time you enter a block
    // All of code in that block indent the same

    // TODO: Remember to change this
    std::cout << "Hello World";  //A single line comment 

    // 4 + 5
    // 4+5

    //Block 1 - logical operation 
    // 
    //Block 2 - next logical operation
}

