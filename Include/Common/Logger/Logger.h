#pragma once

#include "Common.h"
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
#include "spdlog/pattern_formatter.h"
#include "spdlog/formatter.h"

namespace zeus
{
	BATTLE_API spdlog::level::level_enum GetLogLevel(const std::string& str);

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

		std::string LoggerName;

		ESplitType SplitType = ESplitType::ByHour;

		size_t MaxFileSize = FileSize::GigaByte(1);

		size_t MaxFiles = DEFAULT_MAX_FILES;

		spdlog::level::level_enum LogLevel = spdlog::level::info;

		bool SeparateByYear = false;

		bool SeparateByMonth = false;

		bool SeparateByDay = false;

		std::string Pattern = "[%Y-%m-%d %H:%M:%S.%e] [%l] %v";
	};

	template <typename Mutex>
	class BATTLE_API CustomFileSink
		: public spdlog::sinks::base_sink<Mutex>
	{
	public:

		explicit CustomFileSink(const LoggerConfig& cfg)
			: loggerCfg_(cfg)
			, fileHelper_()
			, nextRotationTimePoint_(TimeUtils::SecondsToTimePoint(Application::GetInstance().GetCurrentSeconds()))
		{
			this->set_level(cfg.LogLevel);
			set_formatter(std::make_unique<spdlog::pattern_formatter>(cfg.Pattern));
			UpdateLogFile();
		}

	protected:

		void sink_it_(const spdlog::details::log_msg& msg) override
		{
			spdlog::memory_buf_t formatted;
			this->formatter_->format(msg, formatted);

			if (ShouldRotate())
			{
				Rotate();
			}

			fileHelper_.write(formatted);
		}

		void flush_() override
		{
			fileHelper_.flush();
		}

	private:

		void UpdateLogFile()
		{
			auto logDir = BuildLogDirectory();
			std::filesystem::create_directories(logDir);
			auto logFilePath = BuildLogFilePath(logDir);
			fileHelper_.open(logFilePath, true);
		}

		void RotateBySize()
		{
			for (size_t i = loggerCfg_.MaxFiles - 1; i > 0; --i)
			{
				std::filesystem::path src = GetLogFilePath(i - 1);
				std::filesystem::path target = GetLogFilePath(i);
				if (std::filesystem::exists(src))
				{
					std::filesystem::rename(src, target);
				}
			}
			std::filesystem::path currentFilePath = GetLogFilePath(0);
			std::filesystem::rename(currentFilePath, GetLogFilePath(1));
			UpdateLogFile();
		}

		std::filesystem::path GetLogFilePath(const size_t index)
		{
			std::filesystem::path logDir = BuildLogDirectory();
			std::string logFilePath = loggerCfg_.FileName.empty()
				? Application::GetInstance().GetServiceName() : loggerCfg_.FileName;
			if (index > 0)
			{
				logFilePath += StringUtils::Format(".{}", index);
			}
			logFilePath += ".log";
			return (logDir / logFilePath);
		}

		std::string BuildLogDirectory()
		{
			std::filesystem::path logDir = loggerCfg_.LogDir;

			if (loggerCfg_.SeparateByYear)
			{
				logDir /= std::to_string(Application::GetInstance().GetYear());
			}
			else if (loggerCfg_.SeparateByMonth)
			{
				logDir /= StringUtils::Format("{:04}/{:02}", Application::GetInstance().GetYear(), Application::GetInstance().GetMonth());
			}
			else if (loggerCfg_.SeparateByDay)
			{
				logDir /= StringUtils::Format("{:04}/{:02}/{:02}", Application::GetInstance().GetYear()
					, Application::GetInstance().GetMonth(), Application::GetInstance().GetDay());
			}

			return logDir.string();
		}

		std::string BuildLogFilePath(const std::filesystem::path& logDir)
		{
			std::string logFilePath = loggerCfg_.FileName.empty()
				? Application::GetInstance().GetServiceName() : loggerCfg_.FileName;
			logFilePath += ".log";
			return (logDir / logFilePath).string();
		}

		bool ShouldRotate() const
		{
			if (LoggerConfig::ESplitType::BySize == loggerCfg_.SplitType)
			{
				return fileHelper_.size() >= loggerCfg_.MaxFileSize;
			}
			else if (LoggerConfig::ESplitType::ByHour == loggerCfg_.SplitType)
			{
				auto date = TimeUtils::ToTime(nextRotationTimePoint_);
				return (Application::GetInstance().GetHour() != date.tm_hour);
			}
			else if (LoggerConfig::ESplitType::ByDay == loggerCfg_.SplitType)
			{
				auto date = TimeUtils::ToTime(nextRotationTimePoint_);
				return (Application::GetInstance().GetDay() != date.tm_mday);
			}

			return false;
		}

		void Rotate()
		{
			fileHelper_.close();
			if (LoggerConfig::ESplitType::BySize == loggerCfg_.SplitType)
			{
				RotateBySize();
			}
			else
			{
				UpdateLogFile();
			}
			nextRotationTimePoint_ = TimeUtils::SecondsToTimePoint(Application::GetInstance().GetCurrentSeconds());
		}

	private:

		LoggerConfig loggerCfg_;

		spdlog::details::file_helper fileHelper_;

		std::chrono::system_clock::time_point nextRotationTimePoint_;
	};

	class BATTLE_API LogManager
		: public Singleton<LogManager>
	{
	public:

		LogManager() = default;

	public:

		bool Initialize();

		void Destory();

		bool CreateLogger(const LoggerConfig& cfg);

		std::shared_ptr<spdlog::logger> GetLogger(const std::string& name);

	private:

		bool HasExistsLogger(const std::string& name);

	private:

		std::map<std::string, std::shared_ptr<spdlog::logger>> loggers_;
	};

// 日志宏定义，支持可变参数
#define LOG_TRACE(logger_name, ...) \
    do { \
        auto logger = zeus::LogManager::GetInstance().GetLogger(logger_name); \
        if (logger) { \
            logger->trace(__VA_ARGS__); \
        } \
    } while(0)

#define LOG_DEBUG(logger_name, ...) \
    do { \
        auto logger = LogManager::GetInstance().GetLogger(logger_name); \
        if (logger) { \
            logger->debug(__VA_ARGS__); \
        } \
    } while(0)

#define LOG_INFO(logger_name, ...) \
    do { \
        auto logger = LogManager::GetInstance().GetLogger(logger_name); \
        if (logger) { \
            logger->info(__VA_ARGS__); \
        } \
    } while(0)

#define LOG_WARN(logger_name, ...) \
    do { \
        auto logger = LogManager::GetInstance().GetLogger(logger_name); \
        if (logger) { \
            logger->warn(__VA_ARGS__); \
        } \
    } while(0)

#define LOG_ERROR(logger_name, ...) \
    do { \
        auto logger = LogManager::GetInstance().GetLogger(logger_name); \
        if (logger) { \
            logger->error(__VA_ARGS__); \
        } \
    } while(0)

#define LOG_CRITICAL(logger_name, ...) \
    do { \
        auto logger = LogManager::GetInstance().GetLogger(logger_name); \
        if (logger) { \
            logger->critical(__VA_ARGS__); \
        } \
    } while(0)

} // namespace zeus
