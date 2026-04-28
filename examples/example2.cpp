#include <print.hpp>
#include <fstream>

int main()
{
    std::ofstream file("log.txt");
    print(std::string("hello"), file);
    return 0;
}
