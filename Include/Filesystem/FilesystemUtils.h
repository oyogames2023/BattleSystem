#pragma once

#include "Common.h"
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

		static std::string GetFullFilename(const fs::path& path);

		static void GetFileList(const std::vector<fs::path>& paths, const std::vector<std::string>& extensions
			, std::map<std::string, std::vector<fs::path>>& outputFileList);

		static fs::path GetParentDirectory(const fs::path& path);
	};

} // namespace zeus
