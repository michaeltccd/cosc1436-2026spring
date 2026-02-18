/*
 * Movie Library
 * COSC 1436
 * Spring 2026
 */
#include <iostream>
#include <iomanip>
#include <string>

//Movie definition
struct Movie
{
    //Fields
    std::string title;   // Required, not empty

    std::string genres;  // comma separated list

    int runLength;       // >= 0
    int releaseYear;     // 1900 to 2100

    double userRating;   //1 to 5

    bool isClassic;

    std::string description;  //Optional
};

void main()
{
    Movie movie;

    //Prompt for movie details
    std::cout << "Enter title (required): ";
    std::getline(std::cin, movie.title);

    //Validate title
    if (movie.title == "")
        std::cout << "ERROR: Title is required" << std::endl;

    std::cout << "Enter description: ";
    std::getline(std::cin, movie.description);

    std::cout << "Enter genres: ";
    std::getline(std::cin, movie.genres);

    std::cout << "Enter run length (in minutes): ";
    std::cin >> movie.runLength;

    //Runlength >= 0
    if (movie.runLength < 0)
    {
        std::cout << "ERROR: Run length must be at least 0" << std::endl;
        movie.runLength = 0;
    }

    std::cout << "Enter release year (1900-2100): ";
    std::cin >> movie.releaseYear;

    //ReleaseYear >= 1900 and <= 2100
    if (movie.releaseYear < 1900)
    {
        std::cout << "ERROR: Release Year must be at least 1900" << std::endl;
        movie.releaseYear = 1900;
    }
    if (movie.releaseYear > 2100)
    {
        std::cout << "ERROR: Release Year must be no more than 2100" << std::endl;
        movie.releaseYear = 1900;
    }

    std::cout << "Enter the user rating (1.0-5.0): ";
    std::cin >> movie.userRating;

    char isClassic;
    std::cout << "Is classic (Y/N)? ";
    std::cin >> isClassic;

    // If statement
    //    if_stmt ::= if (Eb) S;
    //
    //Translate to boolean if input is Y then true
    if (isClassic == 'Y')
        movie.isClassic = true;
    if (isClassic == 'y')
        movie.isClassic = true;

    //Validate classic
    if (isClassic != 'Y')
        if (isClassic != 'y')
            if (isClassic != 'N')
                if (isClassic != 'n')
                    std::cout << "ERROR: Must be Y or N" << std::endl; // != Y y N n

    //Display movie details
    std::cout << movie.title << " (" << movie.releaseYear << ")" << std::endl;
    std::cout << "Length (in minutes) " << movie.runLength << std::endl;
    std::cout << "Genre(s): " << movie.genres << std::endl;
    std::cout << "User Rating: " << movie.userRating << std::endl;
    
    std::string classicIndicator = "No";
    if (movie.isClassic)
        classicIndicator = "Yes";
    std::cout << "Classic? " << classicIndicator << std::endl;

    std::cout << movie.description << std::endl;

    // Relational demo
    ////Relational operators
    //// rel_expr ::= Eb rel_op Eb => bool
    //// rel_op ::= > >= < <= == !=
    //// Precedence => below arithmetic but above equality, left associative
    //bool isGreater = 4 > 5;  //false
    //isGreater = 10 >= 3;     //true

    //int x = 10, y = 20;
    //bool areEqual = x == y;     //Equality
    //bool areNotEqual = x != y;  //Inequality

    //// Common C code for boolean since it didn't support it
    //int isCorrect = 0;  //false
    //isCorrect = 10;     //true

    ////areEqual = x == y;  //false, equality
    ////areEqual = x = y;   // true, assignment

    ////areEqual = x == 10;
    ////areEqual = x = 10;

    //// When comparing to constants put the constant first
    ////areEqual = 10 == x;
    ////areEqual = 10 = x;

    //// (In)Equality with floating point types
    //float f1 = 1 / 3;
    //float f2 = 100 / (100 / 30 * 100);

    //// Do not use with floating point values
    //areEqual = f1 == f2;  //Mathematically equal
    //areEqual = f1 >= f2;

    //// Can use with floating point with integer
    //f1 = 100.0;
    //areEqual = f1 == 100;   //True

    //// Strings - works with relational
    ////   Numeric comparison
    ////   Case sensitive
    ////   Locale insensitive (not good for sorting)
    //std::string firstName = "Bob";
    //std::string lastName = "bob";
    //bool isSingularName = firstName == lastName;

    ////Case insensitive string comparison
    //// Use .c_str() to convert C++ string to C
    //int result = _strcmpi("Bob", "bob");
    //isSingularName = _strcmpi(firstName.c_str(), lastName.c_str()) == 0;  //Not equal != 0
}