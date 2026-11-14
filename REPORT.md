# ОТЧЕТ ПО ЛАБОРАТОРНОЙ РАБОТЕ №4

**«Подключение сторонних библиотек (SDK): Boost»**
**Вариант 1 (Boost.Date_Time)**

**Выполнил:** Скрипченко З.А.
**Проверил:** Черненко А.А.

## 1. Цель работы

Приобретение практических навыков подключения и использования сторонних библиотек (SDK) на примере кроссплатформенной библиотеки **Boost**, в частности модуля **Boost.Date_Time** для работы с датами и временем в языке C++.

## 2. Ход выполнения работы

### 2.1. Выбор и подключение библиотеки

В качестве индивидуального задания был выбран **Вариант 1 (Boost.Date_Time)**. Поскольку данный модуль является *header-only* компонентом библиотеки Boost, интеграция была выполнена напрямую через подключение заголовочных файлов без необходимости сборки бинарных файлов утилит `b2`.

Путь к корневой директории библиотеки Boost в системе:
`E:\chernenko\agu\Sdk\worksdk\boost_1_80_0`

### 2.2. Разработка исходного кода

В корне проекта был создан файл `main.cpp`, использующий компоненты `Boost.Gregorian` (для работы с календарными датами) и `Boost.PosixTime` (для работы с точным временем и временными интервалами).

Ниже представлен листинг разработанной программы:

```
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main() {
    std::cout << "=== Lab Work: Boost.Date_Time (Variant 1) ===\n\n";

    // 1. Boost.Gregorian (Работа с датами)
    boost::gregorian::date today = boost::gregorian::day_clock::local_day();
    std::cout << "1. Current Date (Gregorian): " << today << std::endl;

    boost::gregorian::date future_date = today + boost::gregorian::days(45);
    std::cout << "   Date in 45 days: " << future_date << std::endl;

    boost::gregorian::date target_date(2026, 12, 31);
    boost::gregorian::days days_left = target_date - today;
    std::cout << "   Days left until the end of 2026: " << days_left.days() << std::endl;

    std::cout << "   Is current year (" << today.year() << ") a leap year? " 
              << (boost::gregorian::gregorian_calendar::is_leap_year(today.year()) ? "Yes" : "No") 
              << "\n\n";

    // 2. Boost.PosixTime (Работа со временем)
    boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
    std::cout << "2. Current Time (ptime): " << now << std::endl;

    boost::posix_time::time_duration work_shift(3, 15, 0);
    boost::posix_time::ptime shift_end = now + work_shift;
    std::cout << "   Time after shift (+3 hours 15 mins): " << shift_end << std::endl;

    return 0;
}

```


*Скриншот №1: Исходный код программы в среде разработки VS Code.*

### 2.3. Сборка проекта

Для сборки проекта использовалась связка **CMake** и интегрированная среда **VS Code**. Конфигурация автоматически обнаружила header-only библиотеку Boost по указанному пути и успешно сгенерировала файлы проекта MSBuild.


*Скриншот №2: Лог успешной сборки проекта через CMake (код выхода 0).*

## 3. Результаты выполнения

После успешной компиляции был запущен исполняемый файл `build\Debug\SDK.exe`. Программа корректно выполнила все вычисления: определила текущую дату, прибавила 45 дней, рассчитала количество оставшихся дней до конца года, проверила год на високосность, а также вычислила точное время со сдвигом на рабочую смену.


*Скриншот №3: Результат работы программы в терминале.*

## 4. Заключение

В ходе выполнения лабораторной работы были изучены принципы подключения сторонних библиотек на примере **Boost**. На практике освоено применение компонентов `Boost.Gregorian` и `Boost.PosixTime` для решения прикладных задач обработки дат и временных интервалов на языке C++. Цель лабораторной работы полностью достигнута.