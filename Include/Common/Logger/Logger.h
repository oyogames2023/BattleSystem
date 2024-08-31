#pragma once

#include "Commom.h"
#include "Singleton.h"
#include "BattleConfig.h"
#include "spdlog/spdlog.h"

namespace zeus
{

	struct BATTLE_API FileSize
	{
		static constexpr size_t Byte(size_t count = 1)
		{ 
			return count;
		}

		static constexpr size_t KiloByte(size_t count = 1)
		{ 
			return 1024 * count;
		}

		static constexpr size_t MegaByte(size_t count = 1)
		{ 
			return 1024 * 1024 * count;
		}

		static constexpr size_t GigaByte(size_t count = 1)
		{ 
			return 1024 * 1024 * 1024 * count;
		}
	};

	struct BATTLE_API LoggerConfig
	{
		static constexpr size_t DEFAULT_MAX_FILES = 3;

		enum class ESplitType
		{ 
			BySize, 
			ByHour, 
			ByDay
		};

		std::string LogDir = "logs";

		std::string FileName;

		ESplitType SplitType = ESplitType::ByHour;

		size_t MaxFileSize = FileSize::GigaByte(1);

		size_t MaxFiles = DEFAULT_MAX_FILES;

		spdlog::level::level_enum LogLevel = spdlog::level::info;

		bool SeparateByYear = false;

		bool SeparateByMonth = false;

		bool SeparateByDay = false;
	};

	class LogManager
		: public Singleton<LogManager>
	{
	public:

		LogManager() = default;

	public:

		bool Initialize();

		void Destory();

		bool CreateLogger(const LoggerConfig& cfg);

	private:

		std::map < std::string, std::shared_ptr<spdlog::logger>> loggers_;
	};

} // namespace zeus