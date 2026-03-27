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
//   func_decl ::= T id ( [parameter-list] )
//   func_defn ::= func_decl { S* }
//   parameter-list ::= parameter {, parameter}*
//   parameter ::= T id | T& id
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
//        Copy of argument passed to function
//        Function can read and write parameter
//        Changes to parameter have no impact on original argument
//   2) Output (C++: return type)
//        Function provides the value
//        Caller can either use the value or ignore it
//   3) Input/output (pass by reference) (C++: T& id)
//        For life of call, parameter and argument point to the same value in memory
//        Changes made in the function impact the original argument
//        Caller must use an lvalue as the argument
//        Only used in cases where function needs to modify value or for performance reasons
//        Use `T const&` to use pass by reference but not allow function to modify value

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

//Prototypes / forward reference
// Function declaration without the definition
void DisplayError(std::string);
void DisplayWarning(std::string);
void ResetColors();
void SetForegroundColor(ConsoleColor);

//void SuperMultiply(int, int);

//void Multiply(int value, int multiple)
//{
//    SuperMultiply(value, multiple);
//
//    // value = value * multiple
//    value *= multiple;    
//}

// Variables
//  Local - Declared inside a function and has a lifetime tied to the function call
//  Global - Declared outside a function and has program lifetime
//           Used when multiple functions need access to data that is impractical to pass as parameters
//     Issues with globals (and why you will not use them, especially in this class)
//     - Functions are no longer isolated
//     - Initialization order is undefined
//     - Anybody can read and write them

//int g_standardConsoleLineLength = 80;
//int g_maximumLineLength = g_standardConsoleLineLength;
const int g_maximumLineLength = 80; //Only allowed case for a constant

/// @brief Displays a horizontal line.
/// @param width Width of the line
void DisplayLine ( int width )
{
    //int maximumLineLength = -1;

    {
        double width = 24;
        int someValue = width * g_maximumLineLength;
    }

    if (width < 0)
        width = 0;
    else if (width > g_maximumLineLength)
        width = g_maximumLineLength;

    //int width = 10;

    //Logical operation
    std::cout << std::setfill('-') << std::setw(width) << "" << std::setfill(' ') << std::endl;
};

/// @brief Clears the input buffer of extra characters.
void ClearInputBuffer()
{
    std::cin.ignore(INT32_MAX, '\n');        
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

/// @brief Resets the output colors to their default values.
void ResetColors()
{
    std::cout << "\033[0m";
};

/// @brief Sets the output colors for displaying errors.
/// @param color Color to use for the foreground
void SetForegroundColor(ConsoleColor color)
{
    char buffer[10] = {0};
    _itoa_s((int)color, buffer, 10, 10);

    std::string value = "\033[";
    value += buffer;
    value += "m";

    std::cout << value;
};

//Demoing when recursive calls never end
// return - exits function immediately
void Fibonacci(int value)
{
    //Validate parameters
    if (value < 1)
        return;

    //1 * 2 * 3 * N
    //value * Fibonacci(value - 1);
    std::cout << value << std::endl;
    Fibonacci(value - 1);    
}

/// @brief Confirms information from the user
/// @param message Message to display
/// @return true if yes or false if no
bool Confirm(std::string message)
{
    // Confirm
    message += " (Y/N)? ";
    DisplayMessage(ConsoleColor::Cyan, message, false);
    bool confirm = false;
    do
    {
        char choice;
        std::cin >> choice;
        if (choice == 'Y' || choice == 'y')
            return true;
        /*{
            confirm = true;
            break;*/
        else if (choice == 'N' || choice == 'n')
            return false;
        /*{
            confirm = false;
            break;
        };*/
    } while (true);

    //return false;
}

int ReadInt(std::string message, int minValue, int maxValue)
{
    std::cout << message;

    int input;

    do
    {
        std::cin >> input;          

        if (input >= minValue && input <= maxValue)
            return input;

        //TODO: Fix later
        DisplayError("Value is not in expected range");
    } while (true);
}

int ReadInt(std::string message, int minValue)
{
    return ReadInt(message, minValue, INT32_MAX);
}

/// @brief Reads a string from the user
/// @param message Message to display
/// @param required true to indicate a required value
/// @return Input from user
std::string ReadString(std::string message, bool required)
{    
    std::cout << message;

    std::string input;
    do
    {
        std::getline(std::cin, input);

        //Validate
        if (input != "" || !required)
            return input;

        DisplayError("Value is required");
    } while (true);
}

// Function overloading - Overloading a function's name by parameter types
//  1) Each overload must use the same name
//  2) Each overload must have at least one parameter type that is different
// Overload resolution - Process of identifying the unique function overloaded given function arguments
//  1) Compiler starts with all overloads
//  2) For each argument type, remove overloads that do not support the type (or through type coercion)
//  3) Once all arguments checked
//     A) If one function remains, use it
//     B) If multiple functions remain but one is an exact match use it
//     C) If multiple functions remain then error
//     D) If no functions remain then error

/// @brief Reads an optional string
/// @param message Message to display
/// @return Input from user
std::string ReadString(std::string message)
{
    return ReadString(message, false);
}

Movie AddMovie()
{            
    ClearInputBuffer();

    Movie movie;

    //Title is required    
    movie.title = ReadString("Enter title (required): ", true);    
    movie.description = ReadString("Enter description: ");
    
    for (int count = 0; count < 5; ++count)
    {
        std::string genre = ReadString("Enter genre: ", false);        
        if (genre == "")
            break;

        movie.genres += ", " + genre;
    }

    movie.runLength = ReadInt("Enter run length (in minutes): ", 0);
    movie.releaseYear = ReadInt("Enter release year (1900-2100): ", 1900, 2100);

    std::cout << "Enter the user rating (1.0-5.0): ";
    std::cin >> movie.userRating;

    movie.isClassic = Confirm("Is classic?");

    return movie;
}

//TODO: Fix this correctly later
//Movie is pass by reference
// Pass by reference (input/output) T& id
//   Function can modify argument provided by caller
//   Caller must pass a variable
void DeleteMovie(Movie& movie)
{
    // No movie = no work
    if (movie.title == "")
        return;

    // Calling a function returning a value
    //bool confirm = Confirm("Are you sure you want to delete '" + movie.title + "'");

    //Confirm("Hello");

    //Delete
    //if (confirm)
    if (Confirm("Are you sure you want to delete '" + movie.title + "'"))
        movie.title = "";
}

// Pass by reference makes sense when: copying the value is too expensive or large or not allowed
// Make the param constant to avoid modifications
void ViewMovie(Movie const& movie)
{
    //Movie must exist
    if (movie.title == "")
    {
        //std::cout << "No movies in library" << std::endl;
        DisplayWarning("No movies in library");
        return;
    }

    //Display movie details
    std::cout << movie.title << " (" << movie.releaseYear << ")" << std::endl;
    std::cout << "Length (in minutes) " << movie.runLength << std::endl;
    std::cout << "Genre(s): " << movie.genres << std::endl;
    std::cout << "User Rating: " << movie.userRating << std::endl;
    std::cout << "Classic? " << (movie.isClassic ? "Yes" : "No") << std::endl;

    std::cout << movie.description << std::endl;
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
            case MenuCommand::Add: movie = AddMovie();break;            
            case MenuCommand::Edit: DisplayWarning("Edit not implemented");
            case MenuCommand::Delete: DeleteMovie(movie); break;
            case MenuCommand::View: ViewMovie(movie); break;

            case MenuCommand::Quit: quit = true; break;

            //Everything else
            default: DisplayError("Invalid option"); break;
        }                
    }
}
