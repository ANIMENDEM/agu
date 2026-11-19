#include "Calendar.h"

#include <stdexcept>

namespace NCalendar {

bool IsLeapYear(int year) {
    return boost::gregorian::gregorian_calendar::is_leap_year(year);
}

int DaysInMonth(int year, int month) {
    if (month < 1 || month > 12) {
        throw std::out_of_range("Month must be in range [1, 12]");
    }
    return boost::gregorian::gregorian_calendar::end_of_month_day(year, month);
}

bool IsWorkday(Date d) {
    const auto dow = d.day_of_week();
    return dow != boost::date_time::Saturday && dow != boost::date_time::Sunday;
}

bool IsWorkday(Date d, const HolidaySet& holidays) {
    if (!IsWorkday(d)) {
        return false;
    }
    return holidays.find(d) == holidays.end();
}

int CountWorkdays(Date from, Date to) {
    if (from > to) {
        throw std::invalid_argument("Start date 'from' must not be later than end date 'to'");
    }

    int count = 0;
    for (Date cur = from; cur <= to; cur += boost::gregorian::days(1)) {
        if (IsWorkday(cur)) {
            ++count;
        }
    }
    return count;
}

int CountWorkdays(Date from, Date to, const HolidaySet& holidays) {
    if (from > to) {
        throw std::invalid_argument("Start date 'from' must not be later than end date 'to'");
    }

    int count = 0;
    for (Date cur = from; cur <= to; cur += boost::gregorian::days(1)) {
        if (IsWorkday(cur, holidays)) {
            ++count;
        }
    }
    return count;
}

Date AddWorkdays(Date from, int days) {
    if (days == 0) {
        return from;
    }

    Date cur = from;
    const int step = (days > 0) ? 1 : -1;
    int remaining = (days > 0) ? days : -days;

    while (remaining > 0) {
        cur += boost::gregorian::days(step);
        if (IsWorkday(cur)) {
            --remaining;
        }
    }
    return cur;
}

Date AddWorkdays(Date from, int days, const HolidaySet& holidays) {
    if (days == 0) {
        return from;
    }

    Date cur = from;
    const int step = (days > 0) ? 1 : -1;
    int remaining = (days > 0) ? days : -days;

    while (remaining > 0) {
        cur += boost::gregorian::days(step);
        if (IsWorkday(cur, holidays)) {
            --remaining;
        }
    }
    return cur;
}

} // namespace NCalendar