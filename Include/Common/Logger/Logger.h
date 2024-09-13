#pragma once

#include "Commom.h"
#include "Singleton.h"
#include "BattleConfig.h"
#include "TimeUtils.h"
#include "FilesystemUtils.h"
#include "StringUtils.h"
#include "Application.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/base_sink.h"
#include "spdlog/details/file_helper.h"
#include "spdlog/details/null_mutex.h"

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

	template <typename Mutex>
	class CustomFileSink
		: public spdlog::sinks::base_sink<Mutex>
	{
	public:

		explicit CustomFileSink(const LoggerConfig& cfg)
			: loggerCfg_(cfg)
		{
			UpdateLogFile();
		}

	private:

		void UpdateLogFile()
		{

		}

		//std::string BuildLogDirectory()
		//{
		//	using fs = std::filesystem;
		//	
		//	fs::path logDir = loggerCfg_.LogDir;

		//	if (loggerCfg_.SeparateByYear)
		//	{
		//		logDir /= std::to_string(Application::GetInstance().GetYear());
		//	}
		//	else if (loggerCfg_.SeparateByMonth)
		//	{
		//		logDir /= StringUtils::Format("{}-{}", Application::GetInstance().GetYear(), Application::GetInstance().GetMonth());
		//	}
		//	else if (loggerCfg_.SeparateByDay)
		//	{
		//		logDir /= StringUtils::Format("{}-{}", Application::GetInstance().GetYear(), Application::GetInstance().GetMonth()
		//			, Application::GetInstance().GetDay());
		//	}

		//	return logDir.string();
		//}

	private:

		LoggerConfig loggerCfg_;

		spdlog::details::file_helper fileHelper_;

		std::chrono::system_clock::time_point nextRotationTimePoint_;
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
