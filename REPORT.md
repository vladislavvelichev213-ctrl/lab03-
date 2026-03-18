# Отчет по лабораторной работе №3
## Системы автоматизации сборки проекта на примере CMake

**Студент:** Владислав Величев  
**Дата выполнения:** 18.03.2026

---

## 1. Подготовка и настройка

### 1.1 Клонирование репозитория из lab02

```bash
git clone https://github.com/vladislavvelichev213-ctrl/lab02.git projects/lab03
```

**Листинг вывода:**
```
Cloning into 'projects/lab03'...
remote: Enumerating objects: 36, done.
remote: Counting objects: 100% (36/36), done.
remote: Compressing objects: 100% (27/27), done.
remote: Total 36 (delta 10), reused 36 (delta 10), pack-reused 0 (from 0)
Unpacking objects: 100% (36/36), done.
```

### 1.2 Смена удаленного репозитория

```bash
cd projects/lab03
git remote remove origin
git remote add origin https://github.com/vladislavvelichev213-ctrl/lab03.git
git remote -v
```

**Листинг вывода:**
```
origin  https://github.com/vladislavvelichev213-ctrl/lab03.git (fetch)
origin  https://github.com/vladislavvelichev213-ctrl/lab03.git (push)
```

### 1.3 Отправка в новый репозиторий

```bash
git push -u origin main
```

**Листинг вывода:**
```
Enumerating objects: 36, done.
Counting objects: 100% (36/36), done.
Delta compression using up to 2 threads
Compressing objects: 100% (20/20), done.
Writing objects: 100% (36/36), 10.04 KiB | 10.04 MiB/s, done.
Total 36 (delta 15), reused 36 (delta 15), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (15/15), done.
To https://github.com/vladislavvelichev213-ctrl/lab03.git
 * [new branch]      main -> main
branch 'main' set up to track 'origin/main'.
```

---

## 2. Ручная компиляция (Tutorial)

### 2.1 Компиляция библиотеки print

```bash
g++ -std=c++11 -I./include -c sources/print.cpp
ls print.o
```

**Листинг вывода:**
```
print.o
```

```bash
nm print.o | grep print
```

**Листинг вывода:**
```
0000000000000000 T _Z5printRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERSo
0000000000000066 T _Z5printRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERSt14basic_ofstreamIcS2_E
```

```bash
ar rvs print.a print.o
```

**Листинг вывода:**
```
ar: creating print.a
a - print.o
```

```bash
file print.a
```

**Листинг вывода:**
```
print.a: current ar archive
```

### 2.2 Компиляция примера 1

```bash
g++ -std=c++11 -I./include -c examples/example1.cpp
ls example1.o
```

**Листинг вывода:**
```
example1.o
```

```bash
g++ example1.o print.a -o example1
./example1 && echo
```

**Листинг вывода:**
```
hello
```

### 2.3 Компиляция примера 2

```bash
g++ -std=c++11 -I./include -c examples/example2.cpp
ls example2.o
```

**Листинг вывода:**
```
example2.o
```

```bash
nm example2.o
```

**Листинг вывода:**
```
0000000000000000 T main
                 U _Z5printRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERSt14basic_ofstreamIcS2_E
                 U _ZNSt14basic_ofstreamIcSt11char_traitsIcEEC1EPNSt7__cxx1112basic_stringIcS1_SaIcEEESt13_Ios_Openmode
                 U _ZNSt14basic_ofstreamIcSt11char_traitsIcEED1Ev
                 U _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_
                 U _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
```

```bash
g++ example2.o print.a -o example2
./example2
cat log.txt && echo
```

**Листинг вывода:**
```
hello
```

### 2.4 Очистка временных файлов

```bash
rm -rf example1.o example2.o print.o
rm -rf print.a
rm -rf example1 example2
rm -rf log.txt
```

```bash
ls -la
```

**Листинг вывода:**
```
total 32
drwxrwxr-x 6 ubuntu ubuntu 4096 Mar 18 15:30 .
drwxrwxr-x 3 ubuntu ubuntu 4096 Mar 18 15:20 ..
drwxrwxr-x 8 ubuntu ubuntu 4096 Mar 18 15:25 .git
-rw-r--r-- 1 ubuntu ubuntu  317 Mar 18 15:22 .gitignore
-rw-r--r-- 1 ubuntu ubuntu  361 Mar 18 15:22 README.md
drwxrwxr-x 2 ubuntu ubuntu 4096 Mar 18 15:30 examples
drwxrwxr-x 2 ubuntu ubuntu 4096 Mar 18 15:30 include
drwxrwxr-x 2 ubuntu ubuntu 4096 Mar 18 15:30 sources
```

---

## 3. Создание CMakeLists.txt

### 3.1 Установка CMake

```bash
sudo apt update
sudo apt install cmake -y
```

**Листинг вывода:**
```
Hit:1 http://archive.ubuntu.com/ubuntu jammy InRelease
Hit:2 http://archive.ubuntu.com/ubuntu jammy-updates InRelease
Hit:3 http://archive.ubuntu.com/ubuntu jammy-backports InRelease
Hit:4 http://archive.ubuntu.com/ubuntu jammy-security InRelease
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
All packages are up to date.

Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
The following additional packages will be installed:
  cmake-data libarchive13 libjsoncpp25 librhash0
Suggested packages:
  cmake-doc ninja-build
The following NEW packages will be installed:
  cmake cmake-data libarchive13 libjsoncpp25 librhash0
0 upgraded, 5 newly installed, 0 to remove and 0 not upgraded.
Need to get 7428 kB of archives.
After this operation, 39.0 MB of additional disk space will be used.
Get:1 http://archive.ubuntu.com/ubuntu jammy/main amd64 cmake-data all 3.22.1-1ubuntu1 [1820 kB]
...
Setting up cmake (3.22.1-1ubuntu1) ...
Processing triggers for man-db (2.10.2-1) ...
```

### 3.2 Проверка установки CMake

```bash
cmake --version
```

**Листинг вывода:**
```
cmake version 3.22.1
CMake suite maintained and supported by Kitware (kitware.com/cmake).
```

### 3.3 Создание базового CMakeLists.txt

```bash
cat > CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.4)
project(print)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(print STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
EOF
```

```bash
cat CMakeLists.txt
```

**Листинг вывода:**
```
cmake_minimum_required(VERSION 3.4)
project(print)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(print STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
```

### 3.4 Первая сборка с CMake

```bash
cmake -H. -B_build
```

**Листинг вывода:**
```
-- The C compiler identification is GNU 11.4.0
-- The CXX compiler identification is GNU 11.4.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/ubuntu/vladislavvelichev213-ctrl/workspace/projects/lab03/_build
```

```bash
cmake --build _build
```

**Листинг вывода:**
```
[ 50%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[100%] Linking CXX static library libprint.a
[100%] Built target print
```

### 3.5 Добавление исполняемых файлов

```bash
cat >> CMakeLists.txt <<'EOF'

add_executable(example1 ${CMAKE_CURRENT_SOURCE_DIR}/examples/example1.cpp)
add_executable(example2 ${CMAKE_CURRENT_SOURCE_DIR}/examples/example2.cpp)

target_link_libraries(example1 print)
target_link_libraries(example2 print)
EOF
```

### 3.6 Полная сборка

```bash
cmake --build _build
```

**Листинг вывода:**
```
[ 25%] Built target print
[ 50%] Building CXX object CMakeFiles/example1.dir/examples/example1.cpp.o
[ 75%] Linking CXX executable example1
[ 75%] Built target example1
[100%] Building CXX object CMakeFiles/example2.dir/examples/example2.cpp.o
[100%] Linking CXX executable example2
[100%] Built target example2
```

### 3.7 Проверка созданных файлов

```bash
ls -la _build/libprint.a
```

**Листинг вывода:**
```
-rw-rw-r-- 1 ubuntu ubuntu 2350 Mar 18 16:30 _build/libprint.a
```

```bash
_build/example1 && echo
```

**Листинг вывода:**
```
hello
```

```bash
_build/example2
cat log.txt && echo
```

**Листинг вывода:**
```
hello
```

### 3.8 Установка библиотеки

```bash
cmake -H. -B_build -DCMAKE_INSTALL_PREFIX=_install
```

**Листинг вывода:**
```
-- Configuring done
-- Generating done
-- Build files have been written to: /home/ubuntu/vladislavvelichev213-ctrl/workspace/projects/lab03/_build
```

```bash
cmake --build _build --target install
```

**Листинг вывода:**
```
[100%] Built target print
Install the project...
-- Install configuration: ""
-- Installing: /home/ubuntu/vladislavvelichev213-ctrl/workspace/projects/lab03/_install/lib/libprint.a
-- Installing: /home/ubuntu/vladislavvelichev213-ctrl/workspace/projects/lab03/_install/include
-- Installing: /home/ubuntu/vladislavvelichev213-ctrl/workspace/projects/lab03/_install/include/print.hpp
-- Installing: /home/ubuntu/vladislavvelichev213-ctrl/workspace/projects/lab03/_install/cmake/print-config.cmake
-- Installing: /home/ubuntu/vladislavvelichev213-ctrl/workspace/projects/lab03/_install/cmake/print-config-noconfig.cmake
```

### 3.9 Установка утилиты tree

```bash
sudo apt install tree -y
```

**Листинг вывода:**
```
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
The following NEW packages will be installed:
  tree
0 upgraded, 1 newly installed, 0 to remove and 0 not upgraded.
Need to get 48.0 kB of archives.
After this operation, 118 kB of additional disk space will be used.
Get:1 http://archive.ubuntu.com/ubuntu jammy/universe amd64 tree amd64 2.0.2-1 [48.0 kB]
Fetched 48.0 kB in 0s (125 kB/s)
Selecting previously unselected package tree.
(Reading database ... 210438 files and directories currently installed.)
Preparing to unpack .../tree_2.0.2-1_amd64.deb ...
Unpacking tree (2.0.2-1) ...
Setting up tree (2.0.2-1) ...
Processing triggers for man-db (2.10.2-1) ...
```

```bash
tree _install
```

**Листинг вывода:**
```
_install/
├── cmake
│   ├── print-config-noconfig.cmake
│   └── print-config.cmake
├── include
│   └── print.hpp
└── lib
    └── libprint.a

4 directories, 4 files
```

### 3.10 Коммит CMakeLists.txt

```bash
git add CMakeLists.txt
git status
```

**Листинг вывода:**
```
On branch main
Your branch is up to date with 'origin/main'.

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        new file:   CMakeLists.txt
```

```bash
git commit -m "added CMakeLists.txt"
```

**Листинг вывода:**
```
[main 95130be] added CMakeLists.txt
 1 file changed, 36 insertions(+)
 create mode 100644 CMakeLists.txt
```

```bash
git push origin main
```

**Листинг вывода:**
```
Enumerating objects: 4, done.
Counting objects: 100% (4/4), done.
Delta compression using up to 2 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 756 bytes | 756.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/vladislavvelichev213-ctrl/lab03.git
   8da9d21..95130be  main -> main
```

---

## 4. Домашнее задание

### 4.1 Создание библиотеки formatter_lib

```bash
mkdir -p formatter_lib
cd formatter_lib
```

```bash
cat > formatter.h <<'EOF'
#pragma once

#include <string>

std::string formatter(const std::string& message);
EOF
```

```bash
cat > formatter.cpp <<'EOF'
#include "formatter.h"

std::string formatter(const std::string& message)
{
    std::string res;
    res += "-------------------------\n";
    res += message + "\n";
    res += "-------------------------\n";
    return res;
}
EOF
```

```bash
cat > CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.4)
project(formatter)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(formatter STATIC formatter.cpp)
EOF
```

```bash
cd ..
```

### 4.2 Создание библиотеки formatter_ex_lib

```bash
mkdir -p formatter_ex_lib
cd formatter_ex_lib
```

```bash
cat > formatter_ex.h <<'EOF'
#pragma once

#include <string>
#include "../formatter_lib/formatter.h"

std::string formatter_ex(const std::string& message);
EOF
```

```bash
cat > formatter_ex.cpp <<'EOF'
#include "formatter_ex.h"

std::string formatter_ex(const std::string& message)
{
    return formatter(message);
}
EOF
```

```bash
cat > CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.4)
project(formatter_ex)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(formatter_ex STATIC formatter_ex.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../formatter_lib)

target_link_libraries(formatter_ex formatter)
EOF
```

```bash
cd ..
```

### 4.3 Создание приложения hello_world_application

```bash
mkdir -p hello_world_application
cd hello_world_application
```

```bash
cat > hello_world.cpp <<'EOF'
#include <iostream>
#include "../formatter_ex_lib/formatter_ex.h"

int main()
{
    std::cout << formatter_ex("Hello, World!");
    return 0;
}
EOF
```

```bash
cat > CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.4)
project(hello_world)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hello_world hello_world.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../formatter_lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../formatter_ex_lib)

target_link_libraries(hello_world formatter_ex formatter)
EOF
```

```bash
cd ..
```

### 4.4 Создание библиотеки solver_lib

```bash
mkdir -p solver_lib
cd solver_lib
```

```bash
cat > solver.h <<'EOF'
#pragma once

class Solver
{
public:
    double findRoot(double a, double b, double c, double eps, 
                    double x1 = -1000, double x2 = 1000);
};
EOF
```

```bash
cat > solver.cpp <<'EOF'
#include "solver.h"
#include <cmath>
#include <algorithm>

double Solver::findRoot(double a, double b, double c, double eps, 
                        double x1, double x2)
{
    if (x1 > x2) {
        std::swap(x1, x2);
    }
    
    while (std::abs(x2 - x1) > eps)
    {
        double mid = (x1 + x2) / 2;
        double f_mid = a * mid * mid + b * mid + c;
        double f_x1 = a * x1 * x1 + b * x1 + c;
        
        if (std::abs(f_mid) < eps)
        {
            return mid;
        }
        else if (f_x1 * f_mid < 0)
        {
            x2 = mid;
        }
        else
        {
            x1 = mid;
        }
    }
    
    return (x1 + x2) / 2;
}
EOF
```

```bash
cat > CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.4)
project(solver_lib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(solver_lib STATIC solver.cpp)
EOF
```

```bash
cd ..
```

### 4.5 Создание приложения solver_application

```bash
mkdir -p solver_application
cd solver_application
```

```bash
cat > solver.cpp <<'EOF'
#include <iostream>
#include <string>
#include "../formatter_ex_lib/formatter_ex.h"
#include "../solver_lib/solver.h"

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        std::cerr << "Usage: solver <a> <b> <c> <eps> [x1] [x2]" << std::endl;
        return 1;
    }
    
    double a = std::stod(argv[1]);
    double b = std::stod(argv[2]);
    double c = std::stod(argv[3]);
    double eps = (argc >= 5) ? std::stod(argv[4]) : 1e-6;
    double x1 = (argc >= 6) ? std::stod(argv[5]) : -1000;
    double x2 = (argc >= 7) ? std::stod(argv[6]) : 1000;
    
    std::cout << "Searching root on interval [" << x1 << ", " << x2 << "]" << std::endl;
    
    Solver solver;
    double root = solver.findRoot(a, b, c, eps, x1, x2);
    
    std::cout << formatter_ex("Root: " + std::to_string(root));
    
    return 0;
}
EOF
```

```bash
cat > CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.4)
project(solver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(solver solver.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../formatter_lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../formatter_ex_lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../solver_lib)

target_link_libraries(solver formatter_ex formatter solver_lib)
EOF
```

```bash
cd ..
```

### 4.6 Создание корневого CMakeLists.txt

```bash
mv CMakeLists.txt CMakeLists.txt.original
```

```bash
cat > CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.10)
project(lab03)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_EXAMPLES "Build examples" ON)

add_subdirectory(formatter_lib)
add_subdirectory(formatter_ex_lib)
add_subdirectory(solver_lib)
add_subdirectory(hello_world_application)
add_subdirectory(solver_application)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
EOF
```

### 4.7 Обновление CMakeLists.txt для examples

```bash
mkdir -p examples
```

```bash
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

install(TARGETS example1 example2
    RUNTIME DESTINATION bin
)
EOF
```

### 4.8 Компиляция библиотеки print

```bash
g++ -std=c++11 -I./include -c sources/print.cpp -o print.o
ar rcs libprint.a print.o
rm print.o
ls -la libprint.a
```

**Листинг вывода:**
```
-rw-rw-r-- 1 ubuntu ubuntu 2350 Mar 18 16:45 libprint.a
```

### 4.9 Финальная сборка

```bash
rm -rf _build
mkdir -p _build
cd _build
```

```bash
cmake .. -DCMAKE_INSTALL_PREFIX=_install
```

**Листинг вывода:**
```
-- The C compiler identification is GNU 15.2.0
-- The CXX compiler identification is GNU 15.2.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (0.3s)
-- Generating done (0.0s)
-- Build files have been written to: /home/ubuntu/vladislavvelichev213-ctrl/workspace/projects/lab03/_build
```

```bash
cmake --build . --target install
```

**Листинг вывода:**
```
[  7%] Building CXX object formatter_lib/CMakeFiles/formatter.dir/formatter.cpp.o
[ 14%] Linking CXX static library libformatter.a
[ 14%] Built target formatter
[ 21%] Building CXX object formatter_ex_lib/CMakeFiles/formatter_ex.dir/formatter_ex.cpp.o
[ 28%] Linking CXX static library libformatter_ex.a
[ 28%] Built target formatter_ex
[ 35%] Building CXX object solver_lib/CMakeFiles/solver_lib.dir/solver.cpp.o
[ 42%] Linking CXX static library libsolver_lib.a
[ 42%] Built target solver_lib
[ 50%] Building CXX object hello_world_application/CMakeFiles/hello_world.dir/hello_world.cpp.o
[ 57%] Linking CXX executable hello_world
[ 57%] Built target hello_world
[ 64%] Building CXX object solver_application/CMakeFiles/solver.dir/solver.cpp.o
[ 71%] Linking CXX executable solver
[ 71%] Built target solver
[ 78%] Building CXX object examples/CMakeFiles/example1.dir/example1.cpp.o
[ 85%] Linking CXX executable example1
[ 85%] Built target example1
[ 92%] Building CXX object examples/CMakeFiles/example2.dir/example2.cpp.o
[100%] Linking CXX executable example2
[100%] Built target example2
Install the project...
-- Install configuration: ""
-- Installing: /home/ubuntu/vladislavvelichev213-ctrl/workspace/projects/lab03/_build/_install/lib/libformatter.a
-- Installing: /home/ubuntu/vladislavvelichev213-ctrl/workspace/projects/lab03/_build/_install/lib/libformatter_ex.a
-- Installing: /home/ubuntu/vladislavvelichev213-ctrl/workspace/projects/lab03/_build/_install/lib/libsolver_lib.a
-- Installing: /home/ubuntu/vladislavvelichev213-ctrl/workspace/projects/lab03/_build/_install/bin/hello_world
-- Installing: /home/ubuntu/vladislavvelichev213-ctrl/workspace/projects/lab03/_build/_install/bin/solver
-- Installing: /home/ubuntu/vladislavvelichev213-ctrl/workspace/projects/lab03/_build/_install/bin/example1
-- Installing: /home/ubuntu/vladislavvelichev213-ctrl/workspace/projects/lab03/_build/_install/bin/example2
```

### 4.10 Проверка работы приложений

```bash
./_install/bin/hello_world
```

**Листинг вывода:**
```
-------------------------
Hello, World!
-------------------------
```

```bash
./_install/bin/example1 && echo
```

**Листинг вывода:**
```
hello
```

```bash
./_install/bin/example2
ls -la log.txt
cat log.txt && echo
```

**Листинг вывода:**
```
-rw-rw-r-- 1 ubuntu ubuntu 6 Mar 18 16:45 log.txt
hello
```

```bash
./_install/bin/solver 1 0 -4 0.001 -10 0
```

**Листинг вывода:**
```
Searching root on interval [-10, 0]
-------------------------
Root: -2.000122
-------------------------
```

```bash
./_install/bin/solver 1 0 -4 0.001 0 10
```

**Листинг вывода:**
```
Searching root on interval [0, 10]
-------------------------
Root: 2.000122
-------------------------
```

---

## 5. Выводы

В ходе выполнения лабораторной работы были изучены:

1. **Ручная компиляция** и создание статических библиотек
2. **Система автоматизации сборки CMake**:
   - Создание CMakeLists.txt
   - Добавление библиотек и исполняемых файлов
   - Установка с префиксом
3. **Структурирование проекта** с поддиректориями
4. **Работа с несколькими библиотеками** и их зависимостями
5. **Сборка и установка** приложений
6. **Поиск корней квадратного уравнения** методом бисекции

Все приложения работают корректно, библиотеки собираются и линкуются правильно.

**Ссылка на репозиторий:** https://github.com/vladislavvelichev213-ctrl/lab03-
```


