#pragma once

#include "Common.h"
#include "BattleConfig.h"

namespace zeus
{

	class BATTLE_API DateTime
	{
	public:

		DateTime();

		explicit DateTime(const uint64_t seconds);

		explicit DateTime(const uint32_t year, const uint32_t month, const uint32_t day
			, const uint32_t hour = 0, const uint32_t minute = 0, const uint32_t second = 0);

	public:

		bool IsValid() const;

		void FromString(const uint32_t year, const uint32_t month, const uint32_t day
			, const uint32_t hour = 0, const uint32_t minute = 0, const uint32_t second = 0);

		void FromMilliseconds(const uint64_t milliseconds);

		uint64_t GetCurrentMilliseconds() const;

		uint64_t GetCurrentSeconds() const;

		std::string ToString() const;

		uint32_t GetYear() const;

		uint32_t GetMonth() const;

		uint32_t GetDay() const;

		uint32_t GetHour() const;

		uint32_t GetMinute() const;

		uint32_t GetSecond() const;

		uint64_t increaseOffsetSeconds(const uint64_t seconds);

		uint64_t decreaseOffsetSeconds(const uint64_t seconds);

		void SetOffsetSeconds(const uint64_t seconds);

		uint64_t GetOffsetSeconds() const;

		uint64_t increaseOffsetMilliseconds(const uint64_t milliseconds);

		uint64_t decreaseOffsetMilliseconds(const uint64_t milliseconds);

		void SetOffsetMilliseconds(const uint64_t milliseconds);

		uint64_t GetOffsetMilliseconds() const;

	private:

		void UpdateTimeFromTimePoint();

	private:

		std::chrono::system_clock::time_point tp_ = {};

		std::tm tm_ = {};

		uint64_t seconds_ = 0;

		uint64_t offsetSeconds_ = 0;

		uint64_t milliseconds_ = 0;

		uint64_t offsetMilliseconds_ = 0;

		bool isValid_ = true;
	};

} // namespace zeus
