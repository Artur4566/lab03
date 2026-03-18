#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <fstream>
#include <iostream>
#include <string>

// Функция для вывода текста в стандартный поток
void display(const std::string& message, std::ostream& stream = std::cout);

// Функция для записи текста в файл
void write_to_file(const std::string& message, const std::string& filename);

#endif
