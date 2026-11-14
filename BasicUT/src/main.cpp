#include <iostream>
#include <string>
#include "Converter.h"

void PrintUsage()
{
    std::cout << "Usage: --in <input> --ct <conversion_type>\n"
              << "Conversion types:\n"
              << "  0 = MillimeterToMeter\n"
              << "  1 = CentimeterToMeter\n"
              << "  2 = DecimeterToMeter\n"
              << "  3 = MeterToKilometer\n"
              << "  4 = MeterToMillimeter\n"
              << "  5 = MeterToCentimeter\n"
              << "  6 = MeterToDecimeter\n"
              << "  7 = KilometerToMeter\n";
}

int main(int argc, char* argv[])
{
    double input = -1.0;
    int conversionType = -1;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "--in" && i + 1 < argc)
        {
            input = std::stod(argv[i + 1]);
            ++i;
        }
        else if (arg == "--ct" && i + 1 < argc)
        {
            conversionType = std::stoi(argv[i + 1]);
            ++i;
        }
    }

    if (input < 0 || conversionType < 0)
    {
        PrintUsage();
        return 1;
    }

    try
    {
        auto ct = static_cast<NConverter::EConversionType>(conversionType);
        double result = NConverter::Convert(input, ct);
        std::cout << input << " conversion type " << conversionType << " equals " << result << "\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}