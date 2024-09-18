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
		return fs::exists(path) && fs::is_regular_file(path);
	}

	bool FilesystemUtils::IsDirectory(const fs::path& path)
	{
		return fs::exists(path) && fs::is_directory(path);
	}

	std::pair<std::string, std::string> FilesystemUtils::GetFilenameAndExtension(const fs::path& path)
	{
		if (!IsRegularFile(path))
		{
			return {};
		}

		std::string filename = path.stem().string();
		std::string extension = path.extension().string();

		return { filename, extension };
	}

	std::string FilesystemUtils::GetFullFilename(const fs::path& path)
	{
		if (!IsRegularFile(path))
		{
			return {};
		}
		return path.filename().string();
	}

	void FilesystemUtils::GetFileList(const std::vector<fs::path>& paths, const std::vector<std::string>& extensions
		, std::map<std::string, std::vector<fs::path>>& outputFileList)
	{
		outputFileList.clear();
		for (const auto& dirPath : paths)
		{
			if (!IsDirectory(dirPath))
			{
				continue;
			}

			std::vector<fs::path> fileList;
			for (const auto& entry : fs::recursive_directory_iterator(dirPath))
			{
				if (!fs::is_regular_file(entry.status()))
				{
					continue;
				}
				const auto filePath = entry.path();
				const auto filenameAndExtension = GetFilenameAndExtension(filePath);
				if (std::find(extensions.begin(), extensions.end(), filenameAndExtension.second) != extensions.end())
				{
					fileList.push_back(fs::relative(filePath, dirPath));
				}
			}

			if (!fileList.empty())
			{
				outputFileList[dirPath.string()] = fileList;
			}
		}
	}

} // namespace zeus