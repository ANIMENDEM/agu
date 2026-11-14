#pragma once

#include <chrono>
#include <string>

namespace NBenchmark
{

class CTimer
{
public:
    explicit CTimer(const std::string& label); // Конструктор с меткой
    ~CTimer();                                 // Деструктор: выводит затраченное время

private:
    std::string m_label;
    std::chrono::steady_clock::time_point m_startTime; // Используем steady_clock
};

} // namespace NBenchmark