#include <iostream>
#include <string>

int main()
{
    // Имя пользователя
    std::string username;
    
    // Ввод имени
    std::cout << "Введите ваше имя: ";
    std::cin >> username;
    
    // Вывод приветствия
    std::cout << "Привет, " << username << "!" << std::endl;
    return 0;
}
