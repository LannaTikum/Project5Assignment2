// Project V - Assignment #2: Debugging vs Release Coding Practice
// Step #3: Initial Source Code - read StudentData.txt, store into vector

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

    // At this point, "students" holds every parsed student object.
    // No screen output yet - that gets added in Step #4 under _DEBUG.

    return 0;
}