#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main() {
    std::cout << "=== Lab Work: Boost.Date_Time (Variant 1) ===\n\n";

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

    boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
    std::cout << "2. Current Time (ptime): " << now << std::endl;

    boost::posix_time::time_duration work_shift(3, 15, 0);
    boost::posix_time::ptime shift_end = now + work_shift;
    std::cout << "   Time after shift (+3 hours 15 mins): " << shift_end << std::endl;

    return 0;
}