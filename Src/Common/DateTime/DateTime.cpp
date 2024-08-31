#include "DateTime.h"
#include "TimeUtils.h"

namespace zeus
{

	DateTime::DateTime()
		: tp_(std::chrono::system_clock::now())
	{
		UpdateTimeFromTimePoint();
	}

	DateTime::DateTime(const uint64_t seconds)
		: tp_(TimeUtils::SecondsToTimePoint(seconds))
	{
		UpdateTimeFromTimePoint();
	}

	DateTime::DateTime(const uint32_t year, const uint32_t month, const uint32_t day
		, const uint32_t hour, const uint32_t minute, const uint32_t second)
	{
		if (!TimeUtils::ValidateDateTime(year, month, day, hour, minute, second))
		{
			isValid_ = false;
		}
		else
		{
			std::tm tm = {};
			tm.tm_year = year - 1900;
			tm.tm_mon = month - 1;
			tm.tm_mday = day;
			tm.tm_hour = hour;
			tm.tm_min = minute;
			tm.tm_sec = second;
			tp_ = TimeUtils::FromTime(tm);
			UpdateTimeFromTimePoint();
		}
	}

	bool DateTime::IsValid() const
	{
		return isValid_;
	}

	void DateTime::FromString(const uint32_t year, const uint32_t month, const uint32_t day
		, const uint32_t hour, const uint32_t minute, const uint32_t second)
	{
		if (!TimeUtils::ValidateDateTime(year, month, day, hour, minute, second))
		{
			return;
		}

		std::tm tm = {};
		tm.tm_year = year - 1900;
		tm.tm_mon = month - 1;
		tm.tm_mday = day;
		tm.tm_hour = hour;
		tm.tm_min = minute;
		tm.tm_sec = second;
		tp_ = TimeUtils::FromTime(tm);
		UpdateTimeFromTimePoint();
	}

	void DateTime::FromMilliseconds(const uint64_t milliseconds)
	{
		tp_ = TimeUtils::MillisecondsToTimePoint(milliseconds);
		UpdateTimeFromTimePoint();
	}

	uint64_t DateTime::GetCurrentMilliseconds() const
	{
		return milliseconds_;
	}

	uint64_t DateTime::GetCurrentSeconds() const
	{
		return seconds_;
	}

	std::string DateTime::ToString() const
	{
		if (!isValid_)
		{
			return "";
		}

		std::ostringstream ss;
		std::time_t t = std::chrono::system_clock::to_time_t(tp_);
		std::tm* ptm = std::localtime(&t);
		ss << std::put_time(ptm, "%YÄê%mÔÂ%dÈÕ %H:%M:%S");

		return ss.str();
	}

	uint32_t DateTime::GetYear() const
	{
		if (!IsValid())
		{
			return 0;
		}
		
		return (tm_.tm_year + 1900);
	}

	uint32_t DateTime::GetMonth() const
	{
		if (!IsValid())
		{
			return 0;
		}

		return (tm_.tm_mon + 1);
	}

	uint32_t DateTime::GetDay() const
	{
		if (!IsValid())
		{
			return 0;
		}

		return tm_.tm_mday;
	}

	uint32_t DateTime::GetHour() const
	{
		if (!IsValid())
		{
			return 0;
		}

		return tm_.tm_hour;
	}

	uint32_t DateTime::GetMinute() const
	{
		if (!IsValid())
		{
			return 0;
		}

		return tm_.tm_min;
	}

	uint32_t DateTime::GetSecond() const
	{
		if (!IsValid())
		{
			return 0;
		}

		return tm_.tm_sec;
	}

	void DateTime::UpdateTimeFromTimePoint()
	{
		std::time_t t = std::chrono::system_clock::to_time_t(tp_);
		tm_ = *std::localtime(&t);
		auto duration_since_epoch = tp_ - std::chrono::system_clock::time_point{};
		seconds_ = std::chrono::duration_cast<std::chrono::seconds>(duration_since_epoch).count();
		milliseconds_ = std::chrono::duration_cast<std::chrono::milliseconds>(duration_since_epoch).count();
	}

} // namespace zeus