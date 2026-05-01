#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

bool IsValidIdentifier(std::string const& value)
{
    //Starts with _ or letter
    //Consists of only _, letter and digits

    if (value == "")
        return false;

    if (value[0] != '_' && !isalpha(value[0]))
        return false;

    for (int index = 1; index < value.length(); ++index)
        if (value[index] != '_' && !isalnum(value[index]))
            return false;    

    return true;
}

void ClassifyChars()
{
    // Value Classify
    std::cout << std::setw(7) << "Value "
              << std::setw(7) << "Letter? "
        << std::setw(7) << "Digit? "
        << std::setw(7) << "isalnum? "        
        << std::setw(7) << "isspace? "
        << std::setw(7) << "islower? "
        << std::setw(7) << "isupper? "
        << std::setw(7) << "tolower? "
        << std::setw(7) << "toupper? "
              << std::endl;

    // Char classify functions
    //   int func(int ch);  0 = false, everything else = true (1)
    //   isalpha() -> letter (iswalpha)
    //   isdigit() -> number (iswdigit)
    //   isalnum() -> letter or number
    //   isspace() -> whitespace
    //   islower() -> lowercase letter
    //   isupper() -> uppercase letter
    //
    //   tolower() -> lower cases a letter
    //   toupper() -> upper cases a letter
    std::string value;
    std::getline(std::cin, value);

    for (int index = 0; index < value.length(); ++index)
    {
        char input = value[index];

        std::cout << std::setw(7) << input
            << std::setw(7) << (isalpha(input) ? "Y" : "N")
            << std::setw(7) << (isdigit(input) ? "Y" : "N")
            << std::setw(7) << (isalnum(input) ? "Y" : "N")
            << std::setw(7) << (isspace(input) ? "Y" : "N")
            << std::setw(7) << (islower(input) ? "Y" : "N")
            << std::setw(7) << (isupper(input) ? "Y" : "N")
            << std::setw(7) << tolower(input)
            << std::setw(7) << toupper(input)
            << std::endl;

        //if (tolower(input) == 'q')
        //if (input == 'Q' || input == 'q')
        //    break;
    }
    
    std::cout << "C++ identifier? " << (IsValidIdentifier(value) ? "Y" : "N") << std::endl;
}

void CStringDemo()
{
    char letterGrades[5] = {'A', 'B', 'C', 'D', 'F'};
    char* pLetterGrades = letterGrades;

    //Every string ends with a NULL terminator
    char const* name = "Bob";  //Length = 4
    char fixedName[] = "Jean";  // Length = 5

    //Cout sees string
    //std::cout << letterGrades << std::endl;
    //std::cout << name << std::endl;

    //C-string functions 
    //  string functions start with str
    int len = strlen(fixedName);   // strlen(str) returns # of bytes/chars in the string, excluding NULL

    char name1[100] = "Mark";
    char name2[200] = {0};

    //Copying a string
    //strcpy(name2, name1);   // strcpy(target, src) copies src to target, better be big enough, null terminates string
    //strncpy(name2, name1, 100)  //strncpy(target, src, size) copies src to target up to size
    strncpy_s(name2, 200, name1, 100);  //strncpy_s(target, size, src, size) 

    //Concat strings (str += v)
    //strcat(name2, name1);  // strcat(target, src) concats source to target
    //strncat(name2, name1, 100); // strncat(target, src, size) 
    strncat_s(name2, 200, name1, 100); //strncat_s(target, size, src, size) 

    //Comparing strings (x == y)
    int areEqual = _stricmp(name2, name1);   // _stricmp(str1, str2) int (< 0 str1 < str2; = 0 str1 == str2, > 0 str1 > str2)
    areEqual = strcmp(name2, name1); //Case sensitive version

    char fullName[] = "Bob Miller";
    char* pSpace = strstr(fullName, " ");   // strstr(target, stringtofind) char*, pointer to substring or nullptr, case sensitive
    if (pSpace)
    {
        std::cout << "Last name = " << pSpace << std::endl;
    } else {
        std::cout << "No last name" << std::endl;
    }

    // Number conversion
    char number[100] = {0};
    do
    {
        std::cin >> number;

        //int valueEntered = atoi(number);  //atoi (Ascii to Int)
        //double valueEntered = atof(number);  //atof (Ascii to floating point)
        char* endPtr = nullptr;
        int valueEntered = strtol(number, &endPtr, 10);
        std::cout << "Integer value = " << valueEntered << std::endl;
        if (valueEntered == 0)
            break;
    } while (true);

    //int to string
    //_itoa(100, number, 10); //"100"
    _itoa_s(100, number, 100, 10);
}

void CppStringDemo()
{
    std::string name = "Bob";

    // Get the length
    int len = name.length();  //.length() -> # of chars in the string (strlen)

    //Case insensitive comparison _stricmp
    // .c_str() char* returns pointer to C string equivalent
    std::string value1 = "Hello", value2 = "hello";
    bool areEqual = value1 == value2;
    areEqual = _stricmp(value1.c_str(), value2.c_str()) == 0;

    // Assignment (strncpy_s)
    name = "Sue";

    // Concatenation (strncat_s)
    name += " Miller";
    name.append(" Jr");  

    // Clearing a string strcpy(buffer, "");
    name = "";
    name.clear();  

    name = "Sue Miller";

    // Find in string (strstr)
    int index = name.find(" ", 0);   //find(stringtofind, index) -> zero-based index of substring
    if (index >= 0)
    {
        std::string firstName = name.substr(0, index);
        std::string lastName = name.substr(index);  //substr(start, count) returns substring starting at start to count chars
        std::cout << "First name = " << firstName 
                 << " Last name = " << lastName << std::endl;
    }
}

int main()
{
    //ClassifyChars();
    //CStringDemo();
    CppStringDemo();

    //ANSI - 1 byte per char
    char ansiChar = 'A';
    std::string programName = "StringDemo"; //10 chars = 10 bytes
    for (int index = 0; index < 10; ++index)
        std::cout << programName[index];

    //Unicode - 2 bytes per char
    wchar_t unicodeChar = 'A';   //MS only solution
    std::wstring programNameUnicode = L"StringDemo";  //20 bytes
    for (int index = 0; index < 10; ++index)
        std::cout << programNameUnicode[index];

    //Other variants of Unicode (C++ unicode chars)
    //char8_t utf8;
    char16_t utf16;
    char32_t utf32;

    std::string name;
    std::cin >> name;

    std::wstring nameUnicode;
    std::wcin >> nameUnicode;  //Reading unicode string

    //std::cin >> utf32;
}
