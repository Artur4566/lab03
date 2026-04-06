##  ПОЛНЫЙ ТЕКСТ ОТЧЕТА ДЛЯ АРТУРА 


# Отчет по лабораторной работе №3
## Системы автоматизации сборки проекта на примере CMake

**Студент:** Кешишоглян Артур  
**Дата выполнения:** 06.04.2026

---

## 1. Подготовка и настройка

### 1.1 Клонирование репозитория из lab02

```bash
git clone https://github.com/Artur4566/lab02.git projects/lab03
```

**Листинг вывода:**
```
Cloning into 'projects/lab03'...
remote: Enumerating objects: 40, done.
remote: Counting objects: 100% (40/40), done.
remote: Compressing objects: 100% (33/33), done.
remote: Total 40 (delta 13), reused 30 (delta 5), pack-reused 0 (from 0)
Receiving objects: 100% (40/40), 12.33 KiB | 185.00 KiB/s, done.
Resolving deltas: 100% (13/13), done.
```

### 1.2 Смена удаленного репозитория

```bash
cd projects/lab03
git remote remove origin
git remote add origin https://github.com/Artur4566/lab03.git
git push -u origin main
```

**Листинг вывода:**
```
Enumerating objects: 40, done.
Counting objects: 100% (40/40), done.
Delta compression using up to 2 threads
Compressing objects: 100% (25/25), done.
Writing objects: 100% (40/40), 12.33 KiB | 12.33 MiB/s, done.
Total 40 (delta 13), reused 40 (delta 13), pack-reused 0 (from 0)
To https://github.com/Artur4566/lab03.git
 * [new branch]      main -> main
branch 'main' set up to track 'origin/main'.
```

---

## 2. Ручная компиляция (Tutorial)

### 2.1 Компиляция библиотеки print

```bash
g++ -std=c++11 -I./include -c sources/print.cpp
ar rcs libprint.a print.o
```

**Листинг вывода:**
```
ar: creating libprint.a
```

### 2.2 Компиляция примера 1

```bash
g++ -std=c++11 -I./include -c examples/example1.cpp
g++ example1.o libprint.a -o example1
./example1 && echo
```

**Листинг вывода:**
```
hello
```

### 2.3 Компиляция примера 2

```bash
g++ -std=c++11 -I./include -c examples/example2.cpp
g++ example2.o libprint.a -o example2
./example2
cat log.txt && echo
```

**Листинг вывода:**
```
hello
```

---

## 3. Создание CMakeLists.txt

### 3.1 Установка CMake

```bash
sudo apt install cmake -y
cmake --version
```

**Листинг вывода:**
```
cmake version 3.31.6
```

### 3.2 Базовый CMakeLists.txt

```bash
cat > CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.4)
project(print)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(print STATIC sources/print.cpp)
include_directories(include)

add_executable(example1 examples/example1.cpp)
add_executable(example2 examples/example2.cpp)

target_link_libraries(example1 print)
target_link_libraries(example2 print)

install(TARGETS print ARCHIVE DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
EOF
```

### 3.3 Сборка с CMake

```bash
cmake -H. -B_build -DCMAKE_INSTALL_PREFIX=./_install
cmake --build _build
cmake --build _build --target install
tree _install
```

**Листинг вывода:**
```
_install/
├── include
│   └── print.hpp
└── lib
    └── libprint.a

3 directories, 2 files
```

---

## 4. Домашнее задание

### 4.1 Библиотека text_lib

```bash
mkdir -p text_lib
cd text_lib

cat > text_lib.h <<'EOF'
#pragma once
#include <string>
std::string wrap_text(const std::string& message);
EOF

cat > text_lib.cpp <<'EOF'
#include "text_lib.h"
std::string wrap_text(const std::string& message)
{
    std::string result;
    result += "=========================\n";
    result += message + "\n";
    result += "=========================\n";
    return result;
}
EOF

cat > CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.4)
project(text_lib)
set(CMAKE_CXX_STANDARD 11)
add_library(text_lib STATIC text_lib.cpp)
install(TARGETS text_lib ARCHIVE DESTINATION lib)
EOF

cd ..
```

### 4.2 Библиотека text_ext_lib

```bash
mkdir -p text_ext_lib
cd text_ext_lib

cat > text_ext_lib.h <<'EOF'
#pragma once
#include <string>
#include "../text_lib/text_lib.h"
std::string format_extended(const std::string& message);
EOF

cat > text_ext_lib.cpp <<'EOF'
#include "text_ext_lib.h"
std::string format_extended(const std::string& message)
{
    return wrap_text(message);
}
EOF

cat > CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.4)
project(text_ext_lib)
set(CMAKE_CXX_STANDARD 11)
add_library(text_ext_lib STATIC text_ext_lib.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../text_lib)
target_link_libraries(text_ext_lib text_lib)
install(TARGETS text_ext_lib ARCHIVE DESTINATION lib)
EOF

cd ..
```

### 4.3 Приложение greeting_app

```bash
mkdir -p greeting_app
cd greeting_app

cat > greeting_app.cpp <<'EOF'
#include <iostream>
#include "../text_ext_lib/text_ext_lib.h"
int main()
{
    std::cout << format_extended("Hello, World!");
    return 0;
}
EOF

cat > CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.4)
project(greeting_app)
set(CMAKE_CXX_STANDARD 11)
add_executable(greeting_app greeting_app.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../text_lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../text_ext_lib)
target_link_libraries(greeting_app text_ext_lib text_lib)
install(TARGETS greeting_app RUNTIME DESTINATION bin)
EOF

cd ..
```

### 4.4 Библиотека equation_lib

```bash
mkdir -p equation_lib
cd equation_lib

cat > equation_lib.h <<'EOF'
#pragma once
class EquationSolver
{
public:
    double findRoot(double a, double b, double c, double eps,
                    double left = -1000, double right = 1000);
};
EOF

cat > equation_lib.cpp <<'EOF'
#include "equation_lib.h"
#include <cmath>
#include <algorithm>
double EquationSolver::findRoot(double a, double b, double c, double eps,
                                 double left, double right)
{
    if (left > right) std::swap(left, right);
    while (std::abs(right - left) > eps)
    {
        double mid = (left + right) / 2;
        double f_mid = a * mid * mid + b * mid + c;
        double f_left = a * left * left + b * left + c;
        if (std::abs(f_mid) < eps) return mid;
        if (f_left * f_mid < 0) right = mid;
        else left = mid;
    }
    return (left + right) / 2;
}
EOF

cat > CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.4)
project(equation_lib)
set(CMAKE_CXX_STANDARD 11)
add_library(equation_lib STATIC equation_lib.cpp)
install(TARGETS equation_lib ARCHIVE DESTINATION lib)
EOF

cd ..
```

### 4.5 Приложение calc_app

```bash
mkdir -p calc_app
cd calc_app

cat > calc_app.cpp <<'EOF'
#include <iostream>
#include <string>
#include "../text_ext_lib/text_ext_lib.h"
#include "../equation_lib/equation_lib.h"
int main(int argc, char** argv)
{
    if (argc < 4)
    {
        std::cerr << "Usage: calc_app <a> <b> <c> <eps> [left] [right]" << std::endl;
        return 1;
    }
    double a = std::stod(argv[1]);
    double b = std::stod(argv[2]);
    double c = std::stod(argv[3]);
    double eps = (argc >= 5) ? std::stod(argv[4]) : 1e-6;
    double left = (argc >= 6) ? std::stod(argv[5]) : -1000;
    double right = (argc >= 7) ? std::stod(argv[6]) : 1000;
    std::cout << "Searching interval [" << left << ", " << right << "]" << std::endl;
    EquationSolver solver;
    double root = solver.findRoot(a, b, c, eps, left, right);
    std::cout << format_extended("Root: " + std::to_string(root));
    return 0;
}
EOF

cat > CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.4)
project(calc_app)
set(CMAKE_CXX_STANDARD 11)
add_executable(calc_app calc_app.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../text_lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../text_ext_lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../equation_lib)
target_link_libraries(calc_app text_ext_lib text_lib equation_lib)
install(TARGETS calc_app RUNTIME DESTINATION bin)
EOF

cd ..
```

### 4.6 Корневой CMakeLists.txt

```bash
cat > CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.10)
project(lab03)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(text_lib)
add_subdirectory(text_ext_lib)
add_subdirectory(equation_lib)
add_subdirectory(greeting_app)
add_subdirectory(calc_app)
add_subdirectory(examples)
EOF
```

### 4.7 Финальная сборка

```bash
g++ -std=c++11 -I./include -c sources/print.cpp -o print.o
ar rcs libprint.a print.o
rm print.o

cat > examples/CMakeLists.txt <<'EOF'
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_library(print STATIC IMPORTED)
set_target_properties(print PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../libprint.a
)
add_executable(example1 example1.cpp)
add_executable(example2 example2.cpp)
target_link_libraries(example1 print)
target_link_libraries(example2 print)
install(TARGETS example1 example2 RUNTIME DESTINATION bin)
EOF

rm -rf _build _install
mkdir _build && cd _build
cmake .. -DCMAKE_INSTALL_PREFIX=_install
cmake --build . --target install
```

**Листинг вывода:**
```
[ 14%] Built target text_lib
[ 28%] Built target text_ext_lib
[ 42%] Built target equation_lib
[ 57%] Built target greeting_app
[ 71%] Built target calc_app
[ 85%] Built target example1
[100%] Built target example2
Install the project...
-- Installing: .../_install/bin/example1
-- Installing: .../_install/bin/example2
-- Installing: .../_install/lib/libtext_lib.a
-- Installing: .../_install/lib/libtext_ext_lib.a
-- Installing: .../_install/lib/libequation_lib.a
-- Installing: .../_install/bin/greeting_app
-- Installing: .../_install/bin/calc_app
```

### 4.8 Проверка работы

```bash
./_install/bin/greeting_app
```

**Листинг вывода:**
```
=========================
Hello, World!
=========================
```

```bash
./_install/bin/calc_app 1 0 -4 0.001 -10 0
```

**Листинг вывода:**
```
Searching interval [-10, 0]
=========================
Root: -2.000122
=========================
```

```bash
./_install/bin/example1 && echo
./_install/bin/example2
cat log.txt && echo
```

**Листинг вывода:**
```
hello
hello
```

---

## 5. Выводы

В ходе выполнения лабораторной работы были изучены:

1. Ручная компиляция и создание статических библиотек
2. Система автоматизации сборки CMake
3. Структурирование проекта с поддиректориями
4. Работа с несколькими библиотеками и их зависимостями
5. Сборка и установка приложений

Все приложения работают корректно.

**Ссылка на репозиторий:** https://github.com/Artur4566/lab03
```
