#pragma once

namespace NConverter
{

enum class EConversionType
{
    
    MillimeterToMeter,
    CentimeterToMeter,
    DecimeterToMeter,
    MeterToKilometer,
    
   
    MeterToMillimeter,
    MeterToCentimeter,
    MeterToDecimeter,
    KilometerToMeter,

    UnsupportedConversion = 999
};

double Convert(double in, EConversionType ct);

}