#define BOOST_TEST_MODULE CalendarTests
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "Calendar.h"

#include <random>
#include <stdexcept>

namespace bdata = boost::unit_test::data;
using NCalendar::Date;
using NCalendar::HolidaySet;

struct YearHolidaysFixture {
    HolidaySet holidays{
        Date(2025, 1, 1),
        Date(2025, 1, 2),
        Date(2025, 1, 7),
        Date(2025, 2, 24),
        Date(2025, 3, 10),
        Date(2025, 5, 1),
        Date(2025, 5, 9),
        Date(2025, 6, 12),
        Date(2025, 11, 4)
    };
};

BOOST_AUTO_TEST_CASE(TestDaysInMonthExceptions) {
    BOOST_CHECK_EQUAL(NCalendar::DaysInMonth(2024, 2), 29);
    BOOST_CHECK_EQUAL(NCalendar::DaysInMonth(2023, 2), 28);
    BOOST_CHECK_THROW(NCalendar::DaysInMonth(2024, 0), std::out_of_range);
    BOOST_CHECK_THROW(NCalendar::DaysInMonth(2024, 13), std::out_of_range);
    BOOST_CHECK_THROW(NCalendar::DaysInMonth(2024, -5), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(TestCountWorkdaysExceptionsAndIntervals) {
    BOOST_CHECK_EQUAL(NCalendar::CountWorkdays(Date(2025, 5, 1), Date(2025, 5, 4)), 2);
    BOOST_CHECK_EQUAL(NCalendar::CountWorkdays(Date(2025, 5, 3), Date(2025, 5, 3)), 0);
    BOOST_CHECK_EQUAL(NCalendar::CountWorkdays(Date(2025, 5, 1), Date(2025, 5, 1)), 1);
    BOOST_CHECK_THROW(NCalendar::CountWorkdays(Date(2025, 5, 10), Date(2025, 5, 1)), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(TestAddWorkdaysBasic) {
    BOOST_CHECK_EQUAL(NCalendar::AddWorkdays(Date(2025, 5, 2), 1), Date(2025, 5, 5));
    BOOST_CHECK_EQUAL(NCalendar::AddWorkdays(Date(2025, 5, 5), -1), Date(2025, 5, 2));
    BOOST_CHECK_EQUAL(NCalendar::AddWorkdays(Date(2025, 5, 3), 0), Date(2025, 5, 3));
}

BOOST_FIXTURE_TEST_CASE(TestHolidaysWorkdays, YearHolidaysFixture) {
    const Date start(2025, 5, 1);
    const Date end(2025, 5, 9);
    const int plainCount = NCalendar::CountWorkdays(start, end);
    const int holidayCount = NCalendar::CountWorkdays(start, end, holidays);
    BOOST_CHECK_EQUAL(holidayCount, plainCount - 2);

    BOOST_CHECK_EQUAL(NCalendar::AddWorkdays(Date(2025, 4, 30), 1, holidays), Date(2025, 5, 2));
}

BOOST_DATA_TEST_CASE(
    TestIsLeapYearZip,
    bdata::make({1900, 2000, 2023, 2024, 2100}) ^ bdata::make({false, true, false, true, false}),
    year, expected
) {
    BOOST_CHECK_EQUAL(NCalendar::IsLeapYear(year), expected);
}

BOOST_DATA_TEST_CASE(
    TestDaysInMonthCartesian,
    bdata::make({2023, 2024}) * bdata::xrange(1, 13),
    year, month
) {
    int expectedDays = 31;
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        expectedDays = 30;
    } else if (month == 2) {
        expectedDays = NCalendar::IsLeapYear(year) ? 29 : 28;
    }
    BOOST_CHECK_EQUAL(NCalendar::DaysInMonth(year, month), expectedDays);
}

BOOST_DATA_TEST_CASE(
    TestRandomWorkdaysConsistency,
    bdata::xrange(100) ^
    bdata::random((
        bdata::seed = 42,
        bdata::distribution = std::uniform_int_distribution<int>(0, 3650)
    )) ^
    bdata::random((
        bdata::seed = 1337,
        bdata::distribution = std::uniform_int_distribution<int>(-20, 20)
    )),
    idx, dayOffset, n
) {
    boost::ignore_unused(idx);
    const Date baseStart(2020, 1, 1);
    const Date d = baseStart + boost::gregorian::days(dayOffset);
    const Date target = NCalendar::AddWorkdays(d, n);
    const bool dIsWorkday = NCalendar::IsWorkday(d);

    if (n > 0) {
        const int expected = n + (dIsWorkday ? 1 : 0);
        BOOST_CHECK_EQUAL(NCalendar::CountWorkdays(d, target), expected);
    } else if (n < 0) {
        const int absN = -n;
        const int expected = absN + (dIsWorkday ? 1 : 0);
        BOOST_CHECK_EQUAL(NCalendar::CountWorkdays(target, d), expected);
    } else {
        BOOST_CHECK_EQUAL(target, d);
        BOOST_CHECK_EQUAL(NCalendar::CountWorkdays(d, target), dIsWorkday ? 1 : 0);
    }
}