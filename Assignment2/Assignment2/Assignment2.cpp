// source.cpp
// Project V - Assignment #2: Debugging vs Release Coding Practice
//
// Compiler directives used:
//   _DEBUG      -> defined automatically by Visual Studio when Solution
//                  Configuration is set to "Debug" (no action needed by you)
//   PRE_RELEASE -> a directive YOU define manually in Project Properties:
//                  C/C++ > Preprocessor > Preprocessor Definitions
//                  (add PRE_RELEASE on its own line). Only add it when you
//                  want the "pre-release" build; remove it for standard.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct STUDENT_DATA
{
    std::string firstName;
    std::string lastName;
    std::string email;   // only populated in PRE_RELEASE builds
};

// Splits a "First,Last" or "First,Last,email" line on commas
static std::vector<std::string> splitLine(const std::string& line)
{

    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, ','))
    {
        tokens.push_back(token);
    }

    return tokens;
}

int main()
{
#ifdef PRE_RELEASE
    std::cout << "Running: PRE-RELEASE version" << std::endl;
    const std::string fileName = "StudentData_Emails.txt";
#else
    std::cout << "Running: STANDARD version" << std::endl;
    const std::string fileName = "StudentData.txt";
#endif

    std::vector<STUDENT_DATA> students;
    std::ifstream inFile(fileName);

    if (!inFile.is_open())
    {
        std::cout << "ERROR: could not open " << fileName << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inFile, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::vector<std::string> parts = splitLine(line);

        STUDENT_DATA student;
        if (parts.size() >= 2)
        {
            student.firstName = parts[0];
            student.lastName = parts[1];
        }

#ifdef PRE_RELEASE
        if (parts.size() >= 3)
        {
            student.email = parts[2];
        }
#endif

        students.push_back(student);
    }

    inFile.close();

#ifdef _DEBUG
    // Only compiled in when Visual Studio's Solution Configuration = Debug
    std::cout << "\n--- DEBUG: Loaded " << students.size() << " students ---\n";
    for (const auto& s : students)
    {
        std::cout << s.firstName << " " << s.lastName;
#ifdef PRE_RELEASE
        std::cout << " (" << s.email << ")";
#endif
        std::cout << std::endl;
    }
#endif

    return 0;
}
