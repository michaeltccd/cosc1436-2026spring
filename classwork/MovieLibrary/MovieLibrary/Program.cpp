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
        //if (movies[index].title == "") //Find first element that is not assigned
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
void ViewMovie(Movie const* ptrMovie)   //ViewMovie (Movie const& movie) //Pass by value
{
    //Movie tempMovie;
    //ptrMovie = &tempMovie;   // Local variable, not the argument

    //Movie must exist
    //(*ptrMovie).title
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

void PointerDemo()
{
    // Pointer = Memory address (hopefully in the heap)
    int someValue = 100;  //Local variable, stored on call stack, 4 bytes in size
    int* ptrValue;        //Local variable, stored on call stack, 4 or 8 bytes in size
                          //Stores a memory address

    // addressof_op ::= &E
    //    Returns a pointer to the variable
    //    Type is typeof(E)
    ptrValue = &someValue; //Capture memory address of local variable
    std::cout << "Pointer value = " << ptrValue << " "
        << "Dereferenced value = " << *ptrValue << " "
        << "Some Value address = " << &someValue << " "
        << "Some Value value = " << someValue << " "
        << std::endl;

//T* T = int *ptrValue = int
    *ptrValue = 200;

    //Initialize your pointers
    double* ptrRate = nullptr; // Preferred, always use this
    //*ptrRate = NULL; // Old C/C++ code, not recommended or used        
    ptrRate = NULL;
    //*ptrRate = nullptr;

    // Type compatibility rules
    float* pFloat = nullptr;
    int testInt = 10;
    double testDouble = 4.5;
    float testFloat = 8.7;

    pFloat = &testFloat;   //float* = float*
    *pFloat = testInt;     //float = int  (type coercion) 

    // Pointers are same size but derefered values are not => ERROR    // 
    //pFloat = &testDouble;  //float* = double*
    //pFloat = &testInt;      //float* = int*  => ERROR    
    // COMPILER requires that pointers exactly match (no type coercion)

    // Validating pointers
    //  1. Is not null (zero)
    // X 2. Points to garbage (uninitialized)  0xCC, only in debugger
    // X 3. Memory we don't own (if you deref to RW, immediately crash) 

    // Testing for not-null
    //  1. Long way, relational (only equality and inequality make sense)
    if (pFloat != nullptr)    // if (boolValue == true)
        *pFloat = 10;
    //  2. C-way, don't use this
    if (pFloat != NULL)
        *pFloat = 10;
    //  3. Short way, how most C++ programmers do it
    if (pFloat)                // if (boolValue)
        *pFloat = 10;

    // Testing for null
    if (pFloat == nullptr)
        std::cout << "Is null" << std::endl;
    if (!pFloat)
        std::cout << "Is null" << std::endl;

    //Pointers can point to array elements
    double taxRates[5] = {1.2, 3.4, 5.6, 7.8, 9.0};
    double* pTaxRate = nullptr;
    pTaxRate = &taxRates[1];

    Movie movie;
    Movie* pMovie = &movie;

    //Accessing a member
    movie.title = "Jaws";       // Member access dot
    (*pMovie).title = "Jaws 2"; // Member access the long way
    pMovie->title = "Jaws 3";   // Member access for pointers ->

    // Naming pointers
    //   prefix with 'ptr' or 'p'

    //Dereferencing a pointer gives u access to the value stored at that pointer
    // dereference_op ::= * E
    // *ptrValue

    // Type of a pointer is ALWAYS a memory address, int (32- or 64-bit)
    // Derefencing a pointer, the type is the type it points to
    //    T* means pointer to T means the dereferenced value is type T
    //    *(int*) => int
    //    * (double*) => double
}

void DynamicMemoryDemo()
{
    /*while (true)
    {
        Movie* pMovie = new Movie;
        delete pMovie;
    }*/

    //Pointers to existing data (local variables)
    //double taxRate = 4.5;
    //double* pTaxRate = nullptr;

    //do
    //{
    //    //Prompt user for a tax rate
    //    std::cout << "Tax rate? ";
    //    std::cin >> taxRate;
    //    if (taxRate <= 0)
    //        break;

    //    // new_op ::= new T  => returns T*
    //    //  Dynamically allocates memory for a given type
    //    pTaxRate = new double;
    //    *pTaxRate = taxRate;
    //} while (true);

    //std::cout << "Tax rate is " << *pTaxRate << std::endl;
    Movie* pMovie = nullptr;
    while (Confirm("Do you want to add a movie? "))
    {
        //Movie movie = AddMovie();
        pMovie = AddMovie();

        //Before allocating new pointer ensure old pointer is cleaned up
        //if (pMovie)
            //delete pMovie;

        //pMovie = new Movie;
        //pMovie->id = movie.id;
        //pMovie->title = movie.title;
        //pMovie->description = movie.description;
        //pMovie->runLength = movie.runLength;
        //pMovie->releaseYear = movie.releaseYear;
        ////pMovie->genres = movie.genres;
        //pMovie->genreCount = movie.genreCount;
        //pMovie->isClassic = movie.isClassic;
    }

    if (pMovie)
    {
        ViewMovie(pMovie);
        delete pMovie;
        pMovie = nullptr;  //Reset pointer

        delete pMovie;  //Calling delete on a bad or already freed pointer is undefined
                        //Calling delete on nullptr is harmless
    }
}

// Steps to convert from pass by ref (variable/parameter) to pointer
// 1. Change the parameter to a pointer
// 2. Every reference to parameter changes to deref
// 3. Validate the pointer
// 4. (Caller) Change argument to pointer
void CPointerVsReferenceDemo(Movie* movie)  //pass by value
{
    if (!movie)
        return;

    //(*movie).title = ;
    movie->title = "New " + movie->title;
}

void PointerVsReferenceDemo(Movie& movie) //pass by ref
{
    //No need to check for null
    movie.title = "New " + movie.title;    
}

void PointerToReferenceCaller()
{
    Movie movie;

    Movie& refMovie = movie;

    //PointerVsReferenceDemo(movie);  //(&movie)
    CPointerVsReferenceDemo(&movie);  //(&movie)
}

void PointerArithmeticDemo()
{
    int intValue = 20;
    int* pInt = &intValue;

    intValue = intValue + 1;

    //Pointer arithmetic adds/subtracts 1 element size, not 1 byte
    // ptr + N => ptr + (N * sizeof(T))
    int* pNewInt = pInt + 1;   
    std::cout << "Old ptr " << pInt << " Old value " << *pInt << std::endl
              << "New ptr " << pNewInt << " New value" << *pNewInt;

    //Arrays and pointers are interchangeable
    int values[10] = {0};
    pInt = values;

    //Array init
    std::cout << std::endl;
    for (int index = 0; index < 10; ++index)
        values[index] = index + 1;
    for (int index = 0; index < 10; ++index)
        std::cout << values[index] << " ";
    std::cout << std::endl;

    //Can use array or pointer with array syntax
    pInt = values;
    for (int index = 0; index < 10; ++index)
        pInt[index] = index + 2;
    for (int index = 0; index < 10; ++index)
        std::cout << values[index] << " ";
    std::cout << std::endl;

    //Can use array or pointer with pointer syntax
    pInt = values;
    for (int index = 0; index < 10; ++index)
        *(pInt + index) = index + 3;
    for (int index = 0; index < 10; ++index)
        std::cout << values[index] << " ";
    std::cout << std::endl;
}

void DynamicallyAllocateArrayDemo()
{
    int size;
    std::cout << "How many elements do you want? ";
    std::cin >> size;

    //Dynamically allocating an array at runtime
    // Size is not fixed
    double* pValues = new double[size];
    for (int index = 0; index < size; ++index)
        pValues[index] = 0;

    //To clean up an array allocated with new you must use delete array
    //delete pValues;
    delete[] pValues;
    pValues = nullptr;
}

void DisplayString(char const* value)
{
    int intValue = 10;
    const int constValue = 20;

    int* pInt = nullptr;
    int const* pConstInt = nullptr;

    //const correctness - understanding and using const correctly
    // nonconst values to const values
    pConstInt = &intValue;
    //*pConstInt = 30;  //ERROR
       
    // const values to nonconst values
    //pInt = &constValue;  //ERROR
    *pInt = 30;

    const int& constRef = intValue; //Storing ref to non-const in constant
    //pInt = &constRef;  //ERROR
    //pInt = (int*)&constRef; //(int*)(const int*)

    // static_cast<T>(E) -> C++ typecast that does some basic checking
    // const_cast<T>(E) -> C++ removal of const from T
    pInt = const_cast<int*>(&constRef);

    std::cout << value << std::endl;
}

void main()
{
    DisplayString("Hello");

    //DynamicallyAllocateArrayDemo();
    //PointerArithmeticDemo();
    //DynamicMemoryDemo();

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
