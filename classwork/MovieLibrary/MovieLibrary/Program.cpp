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
    
    for (int count = 0; count < MaximumGenres; ++count)
    {
        std::string genre = ReadString("Enter genre: ", false);        
        if (genre == "")
            break;

        movie.genres[count] = genre;
        ++movie.genreCount;
    }

    movie.runLength = ReadInt("Enter run length (in minutes): ", 0);
    movie.releaseYear = ReadInt("Enter release year (1900-2100): ", 1900, 2100);

    std::cout << "Enter the user rating (1.0-5.0): ";
    std::cin >> movie.userRating;

    movie.isClassic = Confirm("Is classic?");

    return movie;
}

//TODO: Fix this correctly later
void DeleteMovie(Movie& movie)
{
    // No movie = no work
    if (movie.title == "")
        return;

    //Delete    
    if (Confirm("Are you sure you want to delete '" + movie.title + "'"))
        movie.title = "";
}

void ViewMovie(Movie const& movie)
{
    //Movie must exist
    if (movie.title == "")
    {
        DisplayWarning("No movies in library");
        return;
    }

    //Display movie details
    std::cout << movie.title << " (" << movie.releaseYear << ")" << std::endl;
    std::cout << "Length (in minutes) " << movie.runLength << std::endl;
    //std::cout << "Genre(s): " << movie.genres << std::endl;
    std::cout << "Genres: ";
    for (int index = 0; index < movie.genreCount; ++index)
    {
        if (index > 0)
            std::cout << ", ";

        std::cout << movie.genres[index];
    }
    std::cout << std::endl;

    std::cout << "User Rating: " << movie.userRating << std::endl;
    std::cout << "Classic? " << (movie.isClassic ? "Yes" : "No") << std::endl;

    std::cout << movie.description << std::endl;
}

void ArrayDemo()
{
    const int MaximumValues = 10;
    int values[MaximumValues];

    // Accessing array elements
    //    array_element ::= arr[index]
    //    index ::= Ei
    // You can read and write element values

    // Index is specified inside brackets (integral)
    // Index is always zero-based
    //    Index 0 = Element 1 
    //    Index 1 = Element 2
    //    Index N = Element N+1
    // Given an array of size M
    //    There are M elements (1-M)
    //    Index is 0 to M - 1
    int thirdElement = values[2];

    values[0] = 10;
    values[1] = 20;
    values[2] = 30;

    //Iterate the elements in an array (0..<size)
    // There is no way at runtime to correctly determine # of elements in the array
    for (int index = 0; index < MaximumValues; ++index)
    //int index = 0;
    //for (int& value: values)
    {
        values[index] = index * 10;
        //value = index++ * 10;
    }

    // for-range statement ::= for (T id : arr)
    // Only works if the array is declared within the same function
    //for (int index = 0; index < MaximumValues; ++index)
    for (int value: values)
    {
        //int value = values[index];
        //std::cout << values[index] << " ";
        std::cout << value << " ";
        value = 0;
    }
}

void ArrayInitDemo()
{
    // Zero array initialization - initialize all elements in the array
    //int daysInMonth[12] = {0};

    // Full array initialization sets all elements in the array
    int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    //Init each element to specific value
    /*daysInMonth[0] = daysInMonth[2] = daysInMonth[4] = daysInMonth[6] = daysInMonth[7] = 
        daysInMonth[9] = daysInMonth[11] = 31;
    daysInMonth[3] = daysInMonth[5] = daysInMonth[8] = daysInMonth[10] = 30;
    daysInMonth[1] = 28;    */

    //Implicit array sizing - when using an array initializater, size of array is optional
    //  Use cases:
    //    1. Size of array will never change for your life
    //    2. string
    std::string monthNames[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    //monthNames[0] = "Jan";
    //monthNames[1] = "Feb";
    //monthNames[2] = "Mar";
    //monthNames[3] = "Apr";
    //monthNames[4] = "May";
    //monthNames[5] = "Jun";
    //monthNames[6] = "Jul";
    //monthNames[7] = "Aug";
    //monthNames[8] = "Sep";
    //monthNames[9] = "Oct";
    //monthNames[10] = "Nov";
    //monthNames[11] = "Dec";

    for (int index = 0; index < 12; ++index)
        std::cout << monthNames[index] << " has " << daysInMonth[index] << " days" << std::endl;

    //Partial array initialization - only some element values are set, the rest are zero initialized
    char name[100] = {'B', 'o', 'b'}; //"Bob"
    char companyName[] = "My Company";

    double rates[5] = {1.2, 3.4, 5.6, 7.8, 9.0};

    int x = 100;
    int numbers[10];
    double r = 5.6;

    // Off by one
    //  Starting at 1 and therefore skipping first element
    //  Indexing to size which is one after the last element
    //Init the array
    for (int index = 0; index < 10; ++index)
        numbers[index] = index + 1;

    for (int index = 0; index < 10; ++index)
        std::cout << numbers[index] << " ";
    std::cout << std::endl;
}

void main()
{
    //ArrayDemo();
    ArrayInitDemo();

    //TODO: Remove once no longer used
    //Movie movie;
    //Movie movie2, movie3, movie4; //Support more than 1 movie
    const int MaximumMovies = 100;
    Movie movies[MaximumMovies];         // Stores 100 movies

    //Array declarations  T id [ Eci ];
    //  Elements are the values stored in an array
    //  Names are plural
    //  All elements have same type
    //  DO NOT USE to store unrelated values just to save variables
    //  Value inside the brackets is the size, number of elements, in the array
    //  Size must be:
    //  1. a compile time constant 
    //  2. > than 0
    //  3. Integer
    //  Array is NOT part of the type
    // Other names for arrays: collection, vector, set, list, array

    // All arrays store their elements contiguously in memory
    // Local variables are stored on stack so be careful of stack space

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
                //Get the movie details
                //Find the first element not being used in the array
                //Store new movie there, if any
                Movie movie = AddMovie();

                int index;
                for (index = 0; index < MaximumMovies; ++index)
                {
                    if (movies[index].title == "") //Find first element that is not assigned
                    {
                        movies[index] = movie;
                        break;
                    }
                }

                //TODO: Clean this up later
                if (index == MaximumMovies)
                    DisplayError("No more space available");

                break;
            }
            case MenuCommand::Edit: DisplayWarning("Edit not implemented");
            case MenuCommand::Delete: DeleteMovie(movies[0]); break;
            case MenuCommand::View:
            {
                for (Movie movie: movies)
                {
                    if (movie.title != "")
                        ViewMovie(movie);
                }
                break;             
            }

            case MenuCommand::Quit: quit = true; break;

            //Everything else
            default: DisplayError("Invalid option"); break;
        }                
    }
}
