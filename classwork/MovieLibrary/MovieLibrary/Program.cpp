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

//C++ enum
enum class MenuCommand
{
    Add = 1,
    Edit = 2,
    Delete = 3,
    View = 4,
    Quit = 5
};

// Function - a reusable block of code that does one logical operation

// Function definition - Defines a function and its implemention
//   func_defn ::= T id ( [parameter-list] ) { S* }
//   parameter-list ::= parameter {, parameter}*
//   parameter ::= T id
// 
//   func_call ::= id ( [arg-list] );
//   arg-list  ::= E {, E}* 
//                
// - functions are actions and should be named as verbs
// - casing: camel or Pascal 
//
// parameter ::= input to a function
// parameter kinds
//   1) Input (pass by value) (C++: T id)
//          Copy of argument passed to function
//          Function can read and write parameter
//          Changes to parameter have no impact on original argument

void Multiply(int value, int multiple)
{
    // value = value * multiple
    value *= multiple;    
}

/// @brief Displays a horizontal line.
/// @param width Width of the line
void DisplayLine ( int width )
{
    //int width = 10;

    //Logical operation
    std::cout << std::setfill('-') << std::setw(width) << "" << std::setfill(' ') << std::endl;
};

/// @brief Resets the output colors to their default values.
void ResetColors()
{
    std::cout << "\033[0m";
};

/// @brief Clears the input buffer of extra characters.
void ClearInputBuffer()
{
    std::cin.ignore(INT32_MAX, '\n');        
};

enum class ConsoleColor
{
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37,
    
    BrightRed = 91,
    BrightGreen = 92,
    BrightYellow = 93,
    BrightBlue = 94,
    BrightMagenta = 95,
    BrightCyan = 96,
    BrightWhite = 97,
};

/// @brief Sets the output colors for displaying errors.
/// @param color Color to use for the foreground
void SetForegroundColor ( ConsoleColor color )
{
    char buffer[10] = {0};
    _itoa_s((int)color, buffer, 10, 10);

    std::string value = "\033[";
    value += buffer;
    value += "m";
    
    std::cout << value;
};

/// @brief Displays a message.
/// @param color Color to show the message in.
/// @param message Message to display.
/// @param includeNewline Add a new line?
void DisplayMessage(ConsoleColor color, std::string message, bool includeNewline)
{
    SetForegroundColor(color);
    
    std::cout << message;;
    if (includeNewline)
        std::cout << std::endl;

    ResetColors();
}

/// @brief Displays an error message.
/// @param message Message to display.
void DisplayError(std::string message)
{
    SetForegroundColor(ConsoleColor::BrightRed);
    std::cout << "ERROR: " << message << std::endl;
    ResetColors();
}

/// @brief Displays a warning message.
/// @param message Message to display.
void DisplayWarning(std::string message)
{
    SetForegroundColor(ConsoleColor::Yellow);
    std::cout << "WARN: " << message << std::endl;
    ResetColors();
}

void Fibonacci(int value)
{
    if (value >= 1)
    {
        //1 * 2 * 3 * N
        //value * Fibonacci(value - 1);
        std::cout << value << std::endl;
        Fibonacci(value - 1);
    };
}

// Main is a special function
// - It is the entry function of your program
// - It's declaration can vary slightly
// - You cannot call main directly
void main()
{
    //Fibonacci(3);

    /*int input = 10;
    int multiple = 5;
    Multiply(input, multiple);
    std::cout << input << std::endl;*/

    Movie movie;

    bool quit = false;
    while (!quit)
    {
        // Display menu
        std::cout << "Main Menu" << std::endl;
        //std::cout << "------------" << std::endl;
        DisplayLine(10);
        std::cout << "A)dd Movie" << std::endl;
        std::cout << "E)dit Movie" << std::endl;
        std::cout << "D)elete Movie" << std::endl;
        std::cout << "V)iew Movie" << std::endl;
        std::cout << "Q)uit" << std::endl;
        std::cout << "? ";

        //Handle user input
        MenuCommand input = (MenuCommand)0;
        char choice;

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

                default:
                {
                    //SetForegroundColor(ConsoleColor::BrightRed);
                    //std::cout << "ERROR: Invalid option" << std::endl; 
                    //ResetColors();
                    DisplayError("Invalid option");
                    break;                    
                }
            }
        }
        
        switch (input)
        {
            case MenuCommand::Add:
            {
                // Add movie logic                
                //Reset input buffer
                //std::cin.ignore(INT32_MAX, '\n');
                ClearInputBuffer();

                //Prompt for movie details
                std::cout << "Enter title (required): ";
                while (movie.title == "")
                {
                    std::getline(std::cin, movie.title);

                    //Validate title
                    if (movie.title == "")
                        DisplayError("Title is required");
                }

                std::cout << "Enter description: ";
                std::getline(std::cin, movie.description);

                std::cout << "Enter genre: ";
               
                for (int count = 0; count < 5; ++count)
                {
                    std::string genre;
                    std::getline(std::cin, genre);

                    if (genre != "")
                    {
                        movie.genres += ", " + genre;
                    } else
                        break;
                }

                std::cout << "Enter run length (in minutes): ";
                do
                {
                    std::cin >> movie.runLength;

                    //Runlength >= 0
                    if (movie.runLength < 0)
                        DisplayError("Run length must be at least 0");
                } while (movie.runLength < 0);

                std::cout << "Enter release year (1900-2100): ";

                //ReleaseYear >= 1900 and <= 2100        
                while (movie.releaseYear < 1900 || movie.releaseYear > 2100)
                {
                    std::cin >> movie.releaseYear;

                    if (movie.releaseYear < 1900 || movie.releaseYear > 2100)
                        DisplayError("Release Year must be between 1900 and 2100");                    
                }

                std::cout << "Enter the user rating (1.0-5.0): ";
                std::cin >> movie.userRating;

                char isClassic;
                std::cout << "Is classic (Y/N)? ";

                do
                {
                    std::cin >> isClassic;

                    if (isClassic == 'Y' || isClassic == 'y')
                    {
                        movie.isClassic = true;
                        break;
                    } else if (isClassic == 'N' || isClassic == 'n')
                    {
                        movie.isClassic = false;
                        break;
                    } else
                        DisplayError("Must be Y or N");
                } while (true);

                break;
            }

            //case 'E': 
            case MenuCommand::Edit: DisplayWarning("Edit not implemented");

            case MenuCommand::Delete:
            {
                // No movie = no work
                if (movie.title == "")
                    break;

                // Confirm
                //std::cout << "Are you sure you want to delete '" << movie.title << "' (Y/N)? ";
                std::string message = "Are you sure you want to delete '";
                message += movie.title;
                message += "' (Y/N)? ";
                DisplayMessage(ConsoleColor::Cyan, message, false);
                bool confirm = false;
                do
                {
                    char choice;
                    std::cin >> choice;
                    if (choice == 'Y' || choice == 'y')
                    {
                        confirm = true;
                        break;
                    } else if (choice == 'N' || choice == 'n')
                    {
                        confirm = false;
                        break;
                    };
                } while (true);

                //Delete
                if (confirm)
                    movie.title = "";

                break;
            }

            case MenuCommand::View:
            {
                //Movie must exist
                if (movie.title == "")
                {
                    //std::cout << "No movies in library" << std::endl;
                    DisplayWarning("No movies in library");
                    break;
                }

                //Display movie details
                std::cout << movie.title << " (" << movie.releaseYear << ")" << std::endl;
                std::cout << "Length (in minutes) " << movie.runLength << std::endl;
                std::cout << "Genre(s): " << movie.genres << std::endl;
                std::cout << "User Rating: " << movie.userRating << std::endl;
                std::cout << "Classic? " << (movie.isClassic ? "Yes" : "No") << std::endl;

                std::cout << movie.description << std::endl;
                break;
            }

            case MenuCommand::Quit: quit = true; break;

            //Everything else
            default: DisplayError("Invalid option"); break;
        }                
    }
}
