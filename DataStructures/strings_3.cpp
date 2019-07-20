
// C++ programs have a concept known as a string table and all string literals in your program are included in the program’s executable.
#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef SSTREAM
#define SSTREAM
#include <sstream>
#endif

#ifndef FSTREAM
#define FSTREAM
#include <fstream>
#endif


#ifndef ARRAY
#define ARRAY
#include <array>
#endif

#ifndef UNORDERED_MAP
#define UNORDERED_MAP
#include <unordered_map>
#endif

#include <cassert>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using namespace std::literals;

#define DEBUG_STRING_LITERALS !NDEBUG

// The string literal in this example is the sentence which is included inside the quote marks and followed by the letter s.
//The compiler will create a table of strings during compilation and place them all together. You can see this string inside the exe file created from the source

namespace
{
const std::string MYSTRING{"This is a string"s};
// char* EDIT_STRING("Attempt to edit");//Always assign old-style string literals to variables of type const char* const
const char *const EDIT_STRING("Attempt to edit");

#if DEBUG_STRING_LITERALS
using StringLiteral = std::string;
#endif

#if DEBUG_STRING_LITERALS
StringLiteral MYSTRING_2{"This is a String_2!"s};
#endif

} // namespace

// int main_stringLiterals()
int main_debugStringLiterals()
{
    cout << MYSTRING << endl;
    cout << EDIT_STRING << endl;
    // EDIT_STRING[0]='a'; // warning read-only variable is not assignable
    //run-time error: ISO C++11 does not allow conversion from string literal to 'char *' [-Wwritable-strings]

#if DEBUG_STRING_LITERALS
    //Removing debug string literals from builds
    cout << MYSTRING_2 << endl;
#endif
    return 0;
}

//Localizing User Facing Text
namespace Localization
{
using StringID = int32_t;
enum class Languages
{
    EN_US,
    EN_GB,
    Number
};
const StringID STRING_COLOR{0};
class Manager
{
  private:
    using Strings = std::unordered_map<StringID, std::string>;
    using StringPacks = std::array<Strings, static_cast<size_t>(Languages::Number)>;
    StringPacks m_StringPacks;
    Strings *m_CurrentStringPack{nullptr};
    // uint32_t m_LanguageIndex;s

  public:
    Manager();
    void SetLanguage(Languages language);
    std::string GetString(StringID stringId) const;
};

// Manager::Manager()
// {
//     static const uint32_t INDEX_EN_US{static_cast<uint32_t>(Languages::EN_US)};
//     m_StringPacks[INDEX_EN_US][STRING_COLOR] = "COLOR"s;
//     static const uint32_t INDEX_EN_GB{static_cast<uint32_t>(Languages::EN_GB)};
//     m_StringPacks[INDEX_EN_GB][STRING_COLOR] = "COLOUR"s;
//     SetLanguage(Languages::EN_US);
// }
void Manager::SetLanguage(Languages language)
{
    m_CurrentStringPack = &(m_StringPacks[static_cast<uint32_t>(language)]);
}

std::string Manager::GetString(StringID stringId) const
{
    std::stringstream resultStream;
    resultStream << "!!!"s;
    resultStream << stringId;
    resultStream << "!!!"s;
    string result{resultStream.str()};
    auto iter = m_CurrentStringPack->find(stringId);
    if (iter != m_CurrentStringPack->end())
    {
        result = iter->second;
    }
    return result;
}


//Reading strings from a file
Manager::Manager()
{
    std::ifstream csvStringFile{"./bin/strings.csv"s};
    assert(csvStringFile);
    if (csvStringFile)
    {
        while (!csvStringFile.eof())
        {
            string line;
            getline(csvStringFile, line);
            if (line.size() > 0)
            {
                // Create a stringstream for the line
                stringstream lineStream{line};
                // Use the line stream to read in the string id
                string stringIdText;
                std::getline(lineStream, stringIdText, ',');
                stringstream idStream{stringIdText};
                uint32_t stringId;
                idStream >> stringId;
                // Loop over the line and read in each string
                uint32_t languageId = 0;
                string stringText;
                while (getline(lineStream, stringText, ','))
                {
                    m_StringPacks[languageId++][stringId] = stringText;
                }
            }
        }
    }
    SetLanguage(Languages::EN_US);
}
//Reading strings from a file - xml - ToDo:???

} // namespace Localization

int main_Localization()
{
    Localization::Manager localizationManager;
    string color{localizationManager.GetString(Localization::STRING_COLOR)};
    cout << "EN_US Localized string: " << color.c_str() << endl;
    localizationManager.SetLanguage(Localization::Languages::EN_GB);
    color = localizationManager.GetString(Localization::STRING_COLOR);
    cout << "EN_GB Localized string: " << color.c_str() << endl;
    color = localizationManager.GetString(1);
    cout << color.c_str() << endl;
    return 0;
}

// Inserting Runtime Data into Strings - using boost/format.hpp - ToDo:???

int main(){
     main_debugStringLiterals();
     main_Localization();
    return 0;
}