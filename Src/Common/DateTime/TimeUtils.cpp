#include "TimeUtils.h"
#include "DateTime.h"

namespace zeus
{

	bool TimeUtils::IsLeapYear(const uint32_t year)
	{
		if ((year % 4) != 0)
		{
			return false;
		}
		if ((year % 100) == 0)
		{
			return ((year % 400) == 0);
		}

		return true;
	}

	uint32_t TimeUtils::GetDaysInMonth(const uint32_t year, const uint32_t month)
	{
		ASSERT_WITH_LOG(month >= 1 && month <= 12, "Month must be between 1 and 12.");
		static const std::vector<uint32_t> daysInMonth = {
			31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
		};

		if (2 == month && IsLeapYear(year))
		{
			return 29;
		}

		return daysInMonth[month - 1];
	}

	bool TimeUtils::ValidateDateTime(const uint32_t year, const uint32_t month, const uint32_t day
		, const uint32_t hour, const uint32_t minute, const uint32_t second)
	{
		ASSERT_WITH_LOG(year >= 1900, "Year must be greater than 1900.");
		ASSERT_WITH_LOG(month >= 1 && month <= 12, "Month must be between 1 and 12.");
		const uint32_t maxDays = GetDaysInMonth(year, month);
		ASSERT_WITH_LOG(day >= 1 && day <= maxDays, "Invalid day: must be between 1 and %u.", maxDays);
		ASSERT_WITH_LOG(23 >= hour, "Invalid hour: must be between 0 and 23.");
		ASSERT_WITH_LOG(59 >= minute, "Invalid minute: must be between 0 and 59.");
		ASSERT_WITH_LOG(59 >= second, "Invalid second: must be between 0 and 59.");

		return true;
	}

	std::chrono::system_clock::time_point TimeUtils::SecondsToTimePoint(const uint64_t seconds)
	{
		auto duration = std::chrono::seconds(seconds);
		
		return std::chrono::system_clock::time_point(duration);
	}

	std::chrono::system_clock::time_point TimeUtils::MillisecondsToTimePoint(const uint64_t milliseconds)
	{
		std::chrono::milliseconds duration(milliseconds);
		std::chrono::time_point<std::chrono::system_clock> epoch(std::chrono::duration<uint64_t>{});

		return (epoch + duration);
	}

	std::chrono::system_clock::time_point TimeUtils::FromTime(std::tm& tm)
	{
		time_t t = std::mktime(&tm);

		return std::chrono::system_clock::from_time_t(t);
	}

	std::tm TimeUtils::ToTime(const std::chrono::system_clock::time_point& tp)
	{
		/*
		auto zt = std::chrono::zoned_time(std::chrono::current_zone(), tp);
		auto ldp = zt.get_local_time();
		auto dp = std::chrono::floor<std::chrono::days>(ldp);
		auto ld = std::chrono::year_month_day{ dp };
		auto tt = std::chrono::hh_mm_ss{ ldp - dp };

		std::tm tm = {};
		tm.tm_year = static_cast<int>(ld.year()) - 1900;
		tm.tm_mon = static_cast<int>((unsigned)ld.month()) - 1;
		tm.tm_mday = static_cast<int>((unsigned)ld.day());
		tm.tm_hour = tt.hours().count();
		tm.tm_min = tt.minutes().count();
		tm.tm_sec = static_cast<int>(tt.seconds().count());
		*/
		auto time_t_c = std::chrono::system_clock::to_time_t(tp);
		std::tm tm = *std::localtime(&time_t_c);

		return tm;
	}

	std::string TimeUtils::FormatYearMonth(const uint32_t year, const uint32_t month)
	{
		std::ostringstream oss;
		oss << year << "-" << std::setfill('0') << std::setw(2) << month;

		return oss.str();
	}

} // namespace zeus
