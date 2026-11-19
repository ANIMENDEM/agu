#pragma once

#include <boost/date_time/gregorian/gregorian.hpp>
#include <set>

namespace NCalendar {

using Date = boost::gregorian::date;
using HolidaySet = std::set<Date>;

bool IsLeapYear(int year);

int DaysInMonth(int year, int month);

int CountWorkdays(Date from, Date to);
int CountWorkdays(Date from, Date to, const HolidaySet& holidays);

Date AddWorkdays(Date from, int days);
Date AddWorkdays(Date from, int days, const HolidaySet& holidays);

bool IsWorkday(Date d);
bool IsWorkday(Date d, const HolidaySet& holidays);

} // namespace NCalendar