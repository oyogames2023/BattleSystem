#include "Logger.h"

namespace zeus
{

	spdlog::level::level_enum GetLogLevel(const std::string& str)
	{
		const std::string level = StringUtils::ToLower(str);

		if (level == "trace")
		{
			return spdlog::level::trace;
		}
		else if (level == "debug")
		{
			return spdlog::level::debug;
		}
		else if (level == "info")
		{
			return spdlog::level::info;
		}
		else if (level == "warn" || level == "warning")
		{
			return spdlog::level::warn;
		}
		else if (level == "err" || level == "error")
		{
			return spdlog::level::err;
		}
		else if (level == "critical" || level == "crit")
		{
			return spdlog::level::critical;
		}
		else if (level == "off")
		{
			return spdlog::level::off;
		}

		return spdlog::level::debug;
	}

	bool LogManager::Initialize()
	{
		return true;
	}

	void LogManager::Destory()
	{

	}

	bool LogManager::CreateLogger(const LoggerConfig& cfg)
	{
		if (HasExistsLogger(cfg.LoggerName))
		{
			return false;
		}

		auto sink = std::make_shared<CustomFileSink<std::mutex>>(cfg);
		auto logger = std::make_shared<spdlog::logger>(cfg.LoggerName, sink);
		logger->set_level(cfg.LogLevel);
		loggers_[cfg.LoggerName] = logger;
		return true;
	}

	std::shared_ptr<spdlog::logger> LogManager::GetLogger(const std::string& name)
	{
		auto it = loggers_.find(name);
		if (loggers_.end() == it)
		{
			return nullptr;
		}
		return it->second;
	}

	bool LogManager::HasExistsLogger(const std::string& name)
	{
		auto it = loggers_.find(name);
		return loggers_.end() != it;
	}

} // namespace zeus
