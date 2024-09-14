#pragma once

#include "Commom.h"
#include "BattleConfig.h"

namespace zeus
{

	namespace fs = std::filesystem;

	class BATTLE_API FilesystemUtils
	{
	public:

		static std::string GetExecutableDirectory();

		static bool IsRegularFile(const fs::path& path);

		static bool IsDirectory(const fs::path& path);

		static std::pair<std::string, std::string> GetFilenameAndExtension(const fs::path& path);
	};

} // namespace zeus
