#include "Logger.h"

int main(int argc, char* argv[])
{
	zeus::LoggerConfig cfg;
	cfg.FileName = "XXGames";
	cfg.LoggerName = "XXGames";
	cfg.LogLevel = spdlog::level::trace;
	cfg.SeparateByDay = true;
	zeus::LogManager::GetInstance().CreateLogger(cfg);

	for (;;)
	{
		LOG_TRACE("XXGames", "This is a test.");
		//auto duration = std::chrono::seconds(1);
		//std::this_thread::sleep_for(duration);
	}

	//LOG_TRACE("XXGames", "This is a test1.");
	//LOG_TRACE("XXGames", "This is a test2.");
	//LOG_TRACE("XXGames", "This is a test3.");

	return 0;
}