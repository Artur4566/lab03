#include "output.hpp"

void display(const std::string& message, std::ostream& stream)
{
    stream << message;
}

void write_to_file(const std::string& message, const std::string& filename)
{
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << message << std::endl;
        file.close();
    }
}
