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
//   func_defn ::= T id () { S* }
// - functions are actions and should be named as verbs
// - casing: camel or Pascal 

/// @brief Displays a horizontal line.
void DisplayLine()
{
    //Logical operation
    std::cout << "-------------" << std::endl;
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

/// @brief Sets the output colors for displaying errors.
void SetErrorColor()
{
    std::cout << "\033[91m";
};

// Main is a special function
// - It is the entry function of your program
// - It's declaration can vary slightly
// - You cannot call main directly
void main()
{
    Movie movie;

    bool quit = false;
    while (!quit)
    {
        // Display menu
        std::cout << "Main Menu" << std::endl;
        //std::cout << "------------" << std::endl;
        DisplayLine();
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
                    SetErrorColor();
                    std::cout << "ERROR: Invalid option" << std::endl; 
                    ResetColors();
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
                        std::cout << "ERROR: Title is required" << std::endl;
                }

                std::cout << "Enter description: ";
                std::getline(std::cin, movie.description);

                std::cout << "Enter genre: ";
               
                for (int count = 0; count < 5; ++count)
                {
                    std::string genre;
                    std::getline(std::cin, genre);

                    //if (genre == "")
                    //    continue;

                    //movie.genres += ", " + genre;
                    if (genre != "")
                    {
                        movie.genres += ", " + genre;
                        //++genreCount;
                    } else
                        //genreCount = 5;                        
                    //    //count = 5;
                        break;
                }

                //HACK: Fix this
                std::cout << "Enter run length (in minutes): ";

                do
                {
                    std::cin >> movie.runLength;

                    //Runlength >= 0
                    if (movie.runLength < 0)
                    {
                        std::cout << "ERROR: Run length must be at least 0" << std::endl;
                        //movie.runLength = 0;
                    }
                } while (movie.runLength < 0);

                std::cout << "Enter release year (1900-2100): ";

                //ReleaseYear >= 1900 and <= 2100        
                while (movie.releaseYear < 1900 || movie.releaseYear > 2100)
                {
                    std::cin >> movie.releaseYear;

                    if (movie.releaseYear < 1900 || movie.releaseYear > 2100)
                    {
                        std::cout << "ERROR: Release Year must be between 1900 and 2100" << std::endl;
            //            movie.releaseYear = 1900;
                    }
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
                        //done = true;
                        break;
                    } else if (isClassic == 'N' || isClassic == 'n')
                    {
                        movie.isClassic = false;
                        //done = true;
                        break;
                    } else
                        std::cout << "ERROR: Must be Y or N" << std::endl; // != Y y N n
                } while (true);

                break;
            }

            //case 'E': 
            case MenuCommand::Edit: std::cout << "Edit not implemented" << std::endl; break;

            case MenuCommand::Delete:
            {
                // No movie = no work
                if (movie.title == "")
                    break;

                // Confirm
                std::cout << "Are you sure you want to delete '" << movie.title << "' (Y/N)? ";
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
                    std::cout << "No movies in library" << std::endl;
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
            default: std::cout << "ERROR: Invalid option" << std::endl; break;
        }                
    }
}
