#include "Timer.h"
#include <iostream>

namespace NBenchmark
{

CTimer::CTimer(const std::string& label)
    : m_label(label), m_startTime(std::chrono::steady_clock::now())
{
}

CTimer::~CTimer()
{
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - m_startTime).count();
    
    std::cout << m_label << ": " << duration << " microseconds\n";
}

} // namespace NBenchmark