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

    int runLength = 0;       // >= 0
    int releaseYear = 0;     // 1900 to 2100

    double userRating = 0;   //1 to 5

    bool isClassic = false;

    std::string description;  //Optional
};

//Enumeration - subrange of integers
enum MENU_COMMAND
{
    //Enum values
    MC_ADD = 1,    // const int ADD = 0
    MC_EDIT = 2,   // = 1
    MC_DELETE = 3, // const int DELETE = 3
    MC_VIEW = 4,

    MC_QUIT = 5
};

enum ENHANCED_MENU_COMMAND
{
    EMC_INSERT,
    EMC_DELETE      // const int DELETE = 1
};

//C++ enum
enum class MenuCommand
{
    Add = 1,
    Edit = 2,
    Delete = 3,
    View = 4,
    Quit = 5
};

enum class EnhancedMenuCommand
{
    Insert,
    Delete
};

void main()
{
    // Demo
    //int someValue = 20; 
    //
    //// Side effect = consequences of evaluating the expression
    ////++someValue;   // prefix inc: Increments someValue by 1 and stores it back into someValue (someValue += 1)
    //std::cout << ++someValue << " " << someValue << std::endl;
    //
    ////someValue++;   // postfix inc: Increments someValue by 1 and stores it back into someValue (someValue += 1)
    ////std::cout << someValue << std::endl;
    //std::cout << someValue++ << " " << someValue << std::endl;
    //
    ////--someValue;   // prefix dec: Decrements someValue by 1 and stores it back into someValue (someValue -= 1)
    ////std::cout << someValue << std::endl;
    //std::cout << --someValue << " " << someValue << std::endl;
    //
    ////someValue--;   // postfix decc: Decrements someValue by 1 and stores it back into someValue (someValue -= 1)
    ////    std::cout << someValue << std::endl;
    //std::cout << someValue-- << " " << someValue << std::endl;
    //
    //someValue = 20;
    //std::cout << someValue++ << " " << ++someValue << " " << someValue << std::endl;
    //
    //someValue = 20;
    //if (++someValue > 30 || someValue-- < 10)
    //    std::cout << "Is true: ";
    //std::cout << someValue << std::endl;

    // Display menu
    std::cout << "Main Menu" << std::endl;
    std::cout << "------------" << std::endl;
    std::cout << "A)dd Movie" << std::endl;
    std::cout << "E)dit Movie" << std::endl;
    std::cout << "D)elete Movie" << std::endl;
    std::cout << "V)iew Movie" << std::endl;
    std::cout << "Q)uit" << std::endl;
    std::cout << "? ";

    //Handle user input
    //MENU_COMMAND input = (MENU_COMMAND)0;
    MenuCommand input = (MenuCommand)0;
    char choice;

    // While loop
    //  while_stmt ::= while (Eb) S
    //  Pre-test so S executes 0 or more times
    while (input == (MenuCommand)0)
    {
        std::cin >> choice;
        switch (choice)
        {
            case 'A':
            case 'a': input = MenuCommand::Add; break;

            case 'E':
            case 'e': input = MenuCommand::Edit; break;

            case 'V':
            case 'v': input = MenuCommand::View; break;

            case 'D':
            case 'd': input = MenuCommand::Delete; break;

            case 'Q':
            case 'q': input = MenuCommand::Quit; break;

            default: std::cout << "ERROR: Invalid option" << std::endl; break;
        }
    }
    
    //input = ADD;
    //std::cin >> (int)input;
    //std::cout << (int)input;

    //Handle menu choice
    //if (choice == 'A' || choice == 'a')
    //    //TODO: Move addmovie logic here
    //    std::cout << "Add not implemented" << std::endl;
    //else if (choice == 'E' || choice == 'e')
    //    std::cout << "Edit not implemented" << std::endl;
    //else if (choice == 'D' || choice == 'd')
    //    std::cout << "Delete not implemented" << std::endl;
    //else if (choice == 'V' || choice == 'v')
    //    std::cout << "View not implemented" << std::endl;
    //else
    //    std::cout << "ERROR: Invalid option" << std::endl;
    // 
    // switch_stmt ::= switch (E) { case_statement* }
    // case_stmt ::= case label : S ;
    // label ::= E (compile time constant)
    // Replacement for: if (E == V) elseif (E == V2) elseif ...
    // Limitations
    //   1. Switch expression must be an integral or char
    //   2. All case labels must be compile time constant integers
    //   3. Case labels must be unique  
    // To prevent fallthrough from one case to the next, end your case statements with break    
    switch (input)
    {
        //TODO: Add movie logic here...
        //case 'A':
        //{
        //    //choice = 'a';
        //    //std::cout << "hello";
        //    std::cout << "Add not implemented" << std::endl; 
        //    break;
        //}
        case MenuCommand::Add: std::cout << "Add not implemented" << std::endl; break;

        //case 'E': 
        case MenuCommand::Edit: std::cout << "Edit not implemented" << std::endl; break;

        //case 'D': //std::cout << "Delete not implemented" << std::endl; break;
        case MenuCommand::Delete: std::cout << "Delete not implemented" << std::endl; break;

        //case 'V': //std::cout << "View not implemented" << std::endl; break;
        case MenuCommand::View: std::cout << "View not implemented" << std::endl; break;
        
        case MenuCommand::Quit: std::cout << "Quit not implemented" << std::endl; break;

        //Everything else
        default: std::cout << "ERROR: Invalid option" << std::endl; break;
    }
  
    // Add movie logic
    Movie movie;

    //Reset input buffer
    std::cin.ignore(INT32_MAX, '\n');  

    //Prompt for movie details
    std::cout << "Enter title (required): ";
    while (movie.title == "")
    {
        std::getline(std::cin, movie.title);

        //Validate title
        if (movie.title == "")
            std::cout << "ERROR: Title is required" << std::endl;
    }

    std::cout << "Enter description: ";
    std::getline(std::cin, movie.description);

    std::cout << "Enter genres: ";
    std::getline(std::cin, movie.genres);

    //HACK: Fix this
    std::cout << "Enter run length (in minutes): ";
    movie.runLength = -1;
    while (movie.runLength < 0)
    {
        std::cin >> movie.runLength;

        //Runlength >= 0
        if (movie.runLength < 0)
        {
            std::cout << "ERROR: Run length must be at least 0" << std::endl;
            //movie.runLength = 0;
        }
    }

    std::cout << "Enter release year (1900-2100): ";
    std::cin >> movie.releaseYear;

    //ReleaseYear >= 1900 and <= 2100        
    if (movie.releaseYear < 1900 || movie.releaseYear > 2100)
    {
        std::cout << "ERROR: Release Year must be between 1900 and 2100" << std::endl;
        movie.releaseYear = 1900;
    }

    std::cout << "Enter the user rating (1.0-5.0): ";
    std::cin >> movie.userRating;

    char isClassic;
    std::cout << "Is classic (Y/N)? ";
    std::cin >> isClassic;

    if (isClassic == 'Y' || isClassic == 'y')
        movie.isClassic = true;
    else if (isClassic == 'N' || isClassic == 'n')
        movie.isClassic = false;
    else
    {
        std::cout << "ERROR: Must be Y or N" << std::endl; // != Y y N n
        movie.isClassic = false;
    }     
    
    //Display movie details
    std::cout << movie.title << " (" << movie.releaseYear << ")" << std::endl;
    std::cout << "Length (in minutes) " << movie.runLength << std::endl;
    std::cout << "Genre(s): " << movie.genres << std::endl;
    std::cout << "User Rating: " << movie.userRating << std::endl;
    
    // Conditional operator
    //  conditional_op ::= Eb ? Et : Ef
    // Replaces if-else when calculating a value
    // Et and Ef must be same type
    // Syntax may cause compiler errors in some cases so wrap in parens if necessary
    //std::string classicIndicator = "No";
    //if (movie.isClassic)
    //    classicIndicator = "Yes";
    //std::string classicIndicator = movie.isClassic ? "Yes" : "No";
    std::cout << "Classic? " << (movie.isClassic ? "Yes" : "No") << std::endl;

    std::cout << movie.description << std::endl;
}