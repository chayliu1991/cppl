#pragma once

#include <string>
#include <utility>

#include "Copyable.h"

namespace cppl
{
    class Date : public Copyable
    {
    public:
        struct YearMonthDay
        {
            int year; // [1900..2500]
            int month;
            int day;
        };

        static const int kDaysPerWeek = 7;
        static const int kJulianDayOf1970_01_01;

        Date() : julianDayNumber_(0)
        {
        }

        Date(int year, int month, int day);

        explicit Date(int julianDayNum) : julianDayNumber_(julianDayNum)
        {
        }

        explicit Date(const struct tm &);

        void swap(Date &that)
        {
            std::swap(julianDayNumber_, that.julianDayNumber_);
        }

        bool valid() const { return julianDayNumber_ > 0; }

        std::string toIsoString() const;

        struct YearMonthDay yearMonthDay() const;

        int year() const
        {
            return yearMonthDay().year;
        }

        int month() const
        {
            return yearMonthDay().month;
        }

        int day() const
        {
            return yearMonthDay().day;
        }

        int weekDay() const
        {
            return (julianDayNumber_ + 1) % kDaysPerWeek;
        }

        int julianDayNumber() const { return julianDayNumber_; }

    private:
        int julianDayNumber_;
    };

    inline bool operator<(Date x, Date y)
    {
        return x.julianDayNumber() < y.julianDayNumber();
    }

    inline bool operator==(Date x, Date y)
    {
        return x.julianDayNumber() == y.julianDayNumber();
    }
}