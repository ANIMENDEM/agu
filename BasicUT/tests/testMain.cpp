#include <iostream>
#include <functional>
#include <vector>
#include <stdexcept>
#include <cmath>
#include "../src/Converter.h"

bool IsEqual(double a, double b, double eps = 1e-9)
{
    return std::fabs(a - b) < eps;
}

class CFixture
{
private:
    std::vector<std::pair<std::string, std::function<int()>>> tests;

public:
    void AddTest(const std::string& name, std::function<int()> test)
    {
        tests.push_back({name, test});
    }

    int Run()
    {
        int passed = 0;
        int failed = 0;

        std::cout << "Running " << tests.size() << " tests...\n";
        for (size_t i = 0; i < tests.size(); ++i)
        {
            try
            {
                int res = tests[i].second();
                if (res == 0)
                {
                    std::cout << "[PASS] " << tests[i].first << "\n";
                    passed++;
                }
                else
                {
                    std::cout << "[FAIL] " << tests[i].first << "\n";
                    failed++;
                }
            }
            catch (...)
            {
                std::cout << "[FAIL] " << tests[i].first << " - Unhandled exception\n";
                failed++;
            }
        }

        std::cout << "Results: " << passed << " passed, " << failed << " failed\n";
        return (failed > 0) ? 1 : 0; 
    }
};


int TestNegativeInput()
{
    try
    {
        NConverter::Convert(-1.0, NConverter::EConversionType::MillimeterToMeter);
    }
    catch (const std::invalid_argument&)
    {
        return 0;
    }
    return 1;
}

int TestUnsupportedConversion()
{
    try
    {
        NConverter::Convert(100.0, static_cast<NConverter::EConversionType>(999));
    }
    catch (const std::invalid_argument&)
    {
        return 0;
    }
    return 1;
}

int TestMillimeterToMeter()
{
    double res = NConverter::Convert(1500.0, NConverter::EConversionType::MillimeterToMeter);
    return IsEqual(res, 1.5) ? 0 : 1;
}

int TestCentimeterToMeter()
{
    double res = NConverter::Convert(250.0, NConverter::EConversionType::CentimeterToMeter);
    return IsEqual(res, 2.5) ? 0 : 1;
}

int TestDecimeterToMeter()
{
    double res = NConverter::Convert(45.0, NConverter::EConversionType::DecimeterToMeter);
    return IsEqual(res, 4.5) ? 0 : 1;
}

int TestMeterToKilometer()
{
    double res = NConverter::Convert(2500.0, NConverter::EConversionType::MeterToKilometer);
    return IsEqual(res, 2.5) ? 0 : 1;
}

int TestZeroInput()
{
    double res = NConverter::Convert(0.0, NConverter::EConversionType::MillimeterToMeter);
    return IsEqual(res, 0.0) ? 0 : 1;
}

int main()
{
    CFixture f;

    f.AddTest("TestNegativeInput", TestNegativeInput);
    f.AddTest("TestUnsupportedConversion", TestUnsupportedConversion);
    f.AddTest("TestMillimeterToMeter", TestMillimeterToMeter);
    f.AddTest("TestCentimeterToMeter", TestCentimeterToMeter);
    f.AddTest("TestDecimeterToMeter", TestDecimeterToMeter);
    f.AddTest("TestMeterToKilometer", TestMeterToKilometer);
    f.AddTest("TestZeroInput", TestZeroInput);

    return f.Run();
}