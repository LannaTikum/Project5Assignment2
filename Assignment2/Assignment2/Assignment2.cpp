// Project V - Assignment #2: Debugging vs Release Coding Practice
// Step #4: Adding in some _DEBUG functionality

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct STUDENT_DATA
{
    std::string firstName;
    std::string lastName;
    std::string email;
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
    const std::string fileName = "StudentData.txt";

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

        students.push_back(student);
    }

    inFile.close();

#ifdef _DEBUG
    // Only compiled in when Visual Studio's Solution Configuration = Debug.
    // Prints out all loaded student info to the console for debugging.
    std::cout << "--- DEBUG: Loaded " << students.size() << " students ---" << std::endl;
    for (const auto& s : students)
    {
        std::cout << s.firstName << " " << s.lastName << std::endl;
    }
#endif

    return 0;
}