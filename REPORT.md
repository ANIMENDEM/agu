# Отчет по лабораторной работе №1
## «Тестирование и настройка рабочего окружения»

**Студент:** Скрипченко Захар Александрович  
**Группа:** 4ИВТ ТИИ  
**Преподаватель:** Черненко А.  
**Репозиторий:** https://github.com/ANIMENDEM/agu.git  

---

## 1. Цель работы
Настройка локального окружения для разработки на C++, проверка работы инструментов сборки (CMake, MSVC), системы контроля версий (Git, Git Extensions) и среды разработки VS Code с учетом принципа изоляции проектов (каждая лабораторная работа — самостоятельный CMake-проект в своей папке без общего файла `CMakeLists.txt` в корне репозитория).

---

## 2. Ход выполнения работы

### 2.1. Клонирование репозитория и организация структуры
1. Склонирован удаленный репозиторий с GitHub по адресу `https://github.com/ANIMENDEM/agu.git` в локальную директорию `E:\chernenko\agu`.
2. В корне репозитория создан файл `.gitignore`, исключающий временные каталоги сборки:
   ```text
   build/
   ```
3. Для первой лабораторной работы создана изолированная подпапка `EnvironmentTest`, содержащая свой собственный `CMakeLists.txt` и `main.cpp`.

**Структура репозитория:**
```text
agu/
├── .gitignore
├── REPORT.md
└── EnvironmentTest/
    ├── CMakeLists.txt
    └── main.cpp
```

---

### 2.2. Конфигурация и сборка проекта (EnvironmentTest)

* **`EnvironmentTest/CMakeLists.txt`**:
  ```cmake
  cmake_minimum_required(VERSION 3.10)
  project(EnvironmentTest)

  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)

  add_executable(EnvironmentTest main.cpp)
  ```

* **`EnvironmentTest/main.cpp`**:
  ```cpp
  #include <iostream>

  int main() {
      std::cout << "EnvironmentTest OK" << std::endl;
      return 0;
  }
  ```

Конфигурация проекта выполнена путем явного указания исходной директории проекта через флаг `-S`:
```bash
cmake -S EnvironmentTest -B build/EnvironmentTest
```
![Конфигурация CMake](image_0ee37e.png)

Сборка проекта выполнена с помощью инструмента MSBuild:
```bash
cmake --build build/EnvironmentTest
```
![Сборка проекта](image_0ee37b.png)

---

### 2.3. Запуск и проверка работоспособности
Исполняемый файл успешно скомпилирован в директории `build/EnvironmentTest/Debug/`. Выполнен его запуск из терминала:
```bash
.\build\EnvironmentTest\Debug\EnvironmentTest.exe
```
![Запуск и результат](image_0ee378.png)

**Вывод программы в консоли:**
```text
EnvironmentTest OK
```

---

## 3. Фиксация изменений в Git
Все созданные исходные файлы (`.gitignore`, `REPORT.md`, `EnvironmentTest/CMakeLists.txt`, `EnvironmentTest/main.cpp`) проиндексированы в **Git Extensions**, зафиксированы коммитом и отправлены в удаленный репозиторий на GitHub.

---

## 4. Вывод
Рабочее окружение успешно настроено. Принцип независимой сборки изолированных CMake-проектов проверен на практике. Инструменты компиляции (MSVC), сборки (CMake) и контроля версий (Git) функционируют корректно и готовы к выполнению следующих работ (`BasicUT`, `Benchmark`).