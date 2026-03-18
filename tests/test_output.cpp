#include "../library/output.hpp"
#include <fstream>
#include <string>
#include <iostream>

// Простой тест для проверки работы функций
int main()
{
    std::cout << "Запуск тестов..." << std::endl;
    
    // Тест записи в файл
    write_to_file("Тестовое сообщение 1", "test.log");
    write_to_file("Тестовое сообщение 2", "test.log");
    
    std::cout << "Тесты завершены. Проверьте файл test.log" << std::endl;
    return 0;
}
