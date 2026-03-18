#include "../library/output.hpp"

int main()
{
    write_to_file("Первое сообщение в файл", "log.txt");
    write_to_file("Второе сообщение в файл", "log.txt");
    write_to_file("Третье сообщение", "log.txt");
    return 0;
}
