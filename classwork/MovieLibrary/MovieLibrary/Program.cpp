/*
 * Movie Library
 * COSC 1436
 * Spring 2026
 */
#include <iostream>
#include <iomanip>
#include <string>

//Movie definition
const int MaximumGenres = 5;
struct Movie
{
    //Fields
    int id;

    std::string title;   // Required, not empty
    
    std::string genres[MaximumGenres];  
    int genreCount = 0;

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

void DisplayError(std::string);
void DisplayWarning(std::string);
void ResetColors();
void SetForegroundColor(ConsoleColor);

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

/// @brief Reads an int32
/// @param message Message to display
/// @param minValue Minimum value allowed
/// @param maxValue Maximum value allowed
/// @return Integer value from the user
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

/// @brief Reads an int32
/// @param message Message to display
/// @param minValue Minimum value allowed (there is no maximum value)
/// @return Integer value from the user
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

/// @brief Reads an optional string
/// @param message Message to display
/// @return Input from user
std::string ReadString(std::string message)
{
    return ReadString(message, false);
}

/// @brief Find a movie given its ID
/// @param movies Array to search
/// @param size Size of the array
/// @param id ID to search for
/// @return Index of movie, if found
int FindMovieById(Movie* movies[], int size, int id)
{
    for (int index = 0; index < size; ++index)
        if (movies[index] && movies[index]->id == id)
            return index;

    //Not found
    return -1;
}

//Returning pointers from functions is allowed 
// Use cases (cases when memory is still valid after func call returns)
//   1. Dynamically allocated memory
//   2. Returning address of element of array passed as a parameter
//   3. Address of a global variable
// Not use case
//  1. Returning address of local variable or parameter
Movie* AddMovie()
{            
    ClearInputBuffer();

    Movie* ptrMovie = new Movie;

    //Title is required    
    ptrMovie->title = ReadString("Enter title (required): ", true);    
    ptrMovie->description = ReadString("Enter description: ");
    
    for (int count = 0; count < MaximumGenres; ++count)
    {
        std::string genre = ReadString("Enter genre: ", false);        
        if (genre == "")
            break;

        ptrMovie->genres[count] = genre;
        ++ptrMovie->genreCount;
    }

    ptrMovie->runLength = ReadInt("Enter run length (in minutes): ", 0);
    ptrMovie->releaseYear = ReadInt("Enter release year (1900-2100): ", 1900, 2100);

    std::cout << "Enter the user rating (1.0-5.0): ";
    std::cin >> ptrMovie->userRating;

    ptrMovie->isClassic = Confirm("Is classic?");

    return ptrMovie;
}

/// @brief Adds a movie to the list
/// @param movies Movie list
/// @param size Size of list
/// @return Index of added movie
int AddMovie ( Movie* movies[], int size )
{
    //Get the movie details
    Movie* ptrMovie = AddMovie();
    if (!ptrMovie)
        return -1;

    static int id = 1;

    //Find an empty spot in the array
    for (int index = 0; index < size; ++index)
    {
        if (!movies[index])
        {
            //movie.id = id++;
            ptrMovie->id = id++;

            movies[index] = ptrMovie;
            return index;
        }
    }

    return -1;
}

/// @brief Deletes a movie if the user confirms..
/// @param movie Movie to delete
void DeleteMovie(Movie* movie)
{
    // No movie = no work
    if (!movie)
        return;

    //Delete    
    if (Confirm("Are you sure you want to delete '" + movie->title + "'"))
        delete movie;
}

/// @brief Delete a movie
/// @param movies Movie list
/// @param size Size of list
void DeleteMovies(Movie* movies[], int size)
{
    //Determine movie to delete
    int id = ReadInt("Enter ID of the movie to delete: ", 1);

    //Find the movie
    int index = FindMovieById(movies, size, id);
    if (index < 0 || index >= size)
    {
        DisplayWarning("Movie not found");
        return;
    };

    //Delete it
    DeleteMovie(movies[index]);
    movies[index] = nullptr;
}

/// @brief View movie details
/// @param movie Movie to view
void ViewMovie(Movie const* ptrMovie)
{
    if (ptrMovie->title == "")    
        return;    

    //Display movie details
    std::cout << "[" << ptrMovie->id << "] ";
    std::cout << ptrMovie->title << " (" << ptrMovie->releaseYear << ")" << std::endl;
    std::cout << "Length (in minutes) " << ptrMovie->runLength << std::endl;    
    std::cout << "Genres: ";
    for (int index = 0; index < ptrMovie->genreCount; ++index)
    {
        if (index > 0)
            std::cout << ", ";

        std::cout << ptrMovie->genres[index];
    }
    std::cout << std::endl;

    std::cout << "User Rating: " << ptrMovie->userRating << std::endl;
    std::cout << "Classic? " << (ptrMovie->isClassic ? "Yes" : "No") << std::endl;

    std::cout << ptrMovie->description << std::endl;
}

/// @brief Views the movies in the library
/// @param movies Movie array
/// @param size Number of movies in array
void ViewMovies(Movie* movies[], int size)
{
    //For range statement does not work with array parameters
    //for (Movie movie: movies)
    for (int index = 0; index < size; ++index)
    {
        //if (movies[index].title != "")
        if (movies[index])   //Checking for valid pointer
            ViewMovie(movies[index]);
    }
}

void main()
{
    const int MaximumMovies = 100;
    Movie* movies[MaximumMovies] = {0};         // Stores 100 movies

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
                    DisplayError("Invalid option");
                    break;                    
                }
            }
        }
        
        switch (input)
        {
            case MenuCommand::Add:
            {
                int index = AddMovie(movies, MaximumMovies);                
                if (index < 0)
                    DisplayError("No more space available");

                break;
            }
            case MenuCommand::Edit: DisplayWarning("Edit not implemented");
            case MenuCommand::Delete: DeleteMovies(movies, MaximumMovies); break;
            case MenuCommand::View: ViewMovies(movies, MaximumMovies); break;
            
            case MenuCommand::Quit: quit = true; break;

            //Everything else
            default: DisplayError("Invalid option"); break;
        }                
    }
}
