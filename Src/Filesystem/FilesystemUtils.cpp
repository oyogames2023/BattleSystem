#include "FilesystemUtils.h"

#include "uv.h"

namespace zeus
{

	std::string FilesystemUtils::GetExecutableDirectory()
	{
		char path[4096] = { 0 };
		size_t size = sizeof(path);

		if (uv_exepath(path, &size) != 0)
		{
			return "";
		}

		fs::path exePath(path);
		return exePath.parent_path().string();
	}

	bool FilesystemUtils::IsRegularFile(const fs::path& path)
	{
		return fs::is_regular_file(path);
	}

	bool FilesystemUtils::IsDirectory(const fs::path& path)
	{
		return fs::is_directory(path);
	}

	std::pair<std::string, std::string> FilesystemUtils::GetFilenameAndExtension(const fs::path& path)
	{
		if (IsRegularFile(path))
		{
			return {};
		}

		std::string filename = path.stem().string();
		std::string extension = path.extension().string();

		return { filename, extension };
	}

} // namespace zeus