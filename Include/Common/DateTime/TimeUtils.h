#pragma once

#include "Forwards.h"
#include "BattleConfig.h"

namespace zeus
{

	class BATTLE_API TimeUtils
	{
	public:

		static bool IsLeapYear(const uint32_t year);

		static uint32_t GetDaysInMonth(const uint32_t year, const uint32_t month);

		static bool ValidateDateTime(const uint32_t year, const uint32_t month, const uint32_t day
			, const uint32_t hour = 0, const uint32_t minute = 0, const uint32_t second = 0);

		static std::chrono::system_clock::time_point SecondsToTimePoint(const uint64_t seconds);

		static std::chrono::system_clock::time_point MillisecondsToTimePoint(const uint64_t milliseconds);

		static std::chrono::system_clock::time_point FromTime(std::tm& tm);

		static std::tm ToTime(const std::chrono::system_clock::time_point& tp);

		static std::string FormatYearMonth(const uint32_t year, const uint32_t month);
	};

} // namespace zeus