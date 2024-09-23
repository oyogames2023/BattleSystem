#include "Common.h"
#include "GameConfigParser.h"
#include "ProtoUtils.h"
#include "FilesystemUtils.h"

#include "Config/ItemConfig.pb.h"

using namespace zeus;

int main(int argc, char* argv[])
{
	const fs::path executableDir = FilesystemUtils::GetExecutableDirectory();
	const fs::path excelSearchPath = executableDir / "config";
	std::map<std::string, std::vector<fs::path>> excelDirPaths;
	FilesystemUtils::GetFileList({ excelSearchPath }, { ".xlsx" }, excelDirPaths);

	const fs::path protoSearchPath = executableDir / "protos";
	std::map<std::string, std::vector<fs::path>> protoDirPaths;
	FilesystemUtils::GetFileList({ protoSearchPath }, { ".proto" }, protoDirPaths);
	auto protoParser = std::make_shared<ProtoParser>(protoSearchPath);

	const fs::path configPath = executableDir / "config/cplusplus";

	for (const auto& [dirPath, fileList] : protoDirPaths)
	{
		for (const auto& filePath : fileList)
		{
			if (!protoParser->Load(filePath))
			{
				continue;
			}

			std::cout << "Load " << filePath.generic_string() << " success" << std::endl;
		}
	}

	for (const auto& [dirPath, fileList] : excelDirPaths)
	{
		for (const auto& filePath : fileList)
		{
			const auto fullPath = dirPath / filePath;
			auto excelParser = std::make_shared<ExcelParser>();
			if (!excelParser->Load(fullPath))
			{
				continue;
			}

			std::cout << "Load " << fullPath.generic_string() << " success" << std::endl;
			const auto filenameAndExtension = FilesystemUtils::GetFilenameAndExtension(excelParser->GetPath());
			fs::path outputDir = executableDir / "protos" / "config";
			outputDir /= (filenameAndExtension.first + ".proto");
			ProtoGeneratorPtr protoGenerator = std::make_shared<ProtoGenerator>();
			if (!protoGenerator->ParseWorksheets(excelParser, protoParser, outputDir))
			{
				std::cout << "Generate file: " << outputDir.generic_string() << " failed." << std::endl;
				continue;
			}

			std::cout << "Generate file: " << outputDir.generic_string() << " success." << std::endl;

			GameConfigGeneratorPtr configGenerator = std::make_shared<GameConfigGenerator>();
			if (!configGenerator->GenerateConfigParser(protoParser, protoGenerator, configPath))
			{

				continue;
			}
		}

		config::Sheet1 sheet;
	}

	return 0;
}