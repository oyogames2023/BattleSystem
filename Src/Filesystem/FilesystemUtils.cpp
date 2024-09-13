#include "FilesystemUtils.h"

#include "uv.h"

namespace zeus
{

	namespace fs = std::filesystem;

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

} // namespace zeus