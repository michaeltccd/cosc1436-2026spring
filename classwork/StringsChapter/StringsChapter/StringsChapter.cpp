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

int main()
{
    ClassifyChars();

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
