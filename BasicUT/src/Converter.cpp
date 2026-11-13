#include <stdexcept>
#include <cmath>
#include "Converter.h"

namespace NConverter
{

double Convert(double in, EConversionType ct)
{
   
    if (std::isnan(in) || std::isinf(in))
    {
        throw std::invalid_argument("Input value cannot be NaN or infinity");
    }

    if (in < 0)
        throw std::invalid_argument("Input value must be greater than or equal to 0");

    switch (ct)
    {
        
        case EConversionType::MillimeterToMeter:
            return in / 1000;
        case EConversionType::CentimeterToMeter:
            return in / 100;
        case EConversionType::DecimeterToMeter:
            return in / 10;
        case EConversionType::MeterToKilometer:
            return in / 1000;

        
        case EConversionType::MeterToMillimeter:
            return in * 1000;
        case EConversionType::MeterToCentimeter:
            return in * 100;
        case EConversionType::MeterToDecimeter:
            return in * 10;
        case EConversionType::KilometerToMeter:
            return in * 1000;

        default:
            throw std::invalid_argument("Invalid conversion type");
    }
}

}