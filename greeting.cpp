#include <iostream>
#include <string>

int main()
{
    // Переменная для хранения имени пользователя
    std::string username;
    
    // Запрос имени у пользователя
    std::cout << "Введите ваше имя: ";
    std::cin >> username;
    
    // Вывод приветствия
    std::cout << "Привет, " << username << "!" << std::endl;
    return 0;
}
