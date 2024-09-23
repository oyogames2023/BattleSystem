#include "Common.h"
#include "FilesystemUtils.h"
#include "ProtoUtils.h"

#include <google/protobuf/descriptor.h>
#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/text_format.h>

using namespace zeus;


int main(int argc, char* argv[])
{
	fs::path filePath = FilesystemUtils::GetExecutableDirectory();
	filePath /= "protos";

	google::protobuf::compiler::DiskSourceTree sourceTree;
	sourceTree.MapPath("", filePath.generic_string());
	ProtoErrorCollector errorCollector;
	google::protobuf::compiler::Importer importer(&sourceTree, &errorCollector);

	std::map<std::string, std::vector<fs::path>> dirFileList;
	std::vector<fs::path> filePaths = { filePath };
	std::vector<std::string> fileExtensions = { ".proto" };
	FilesystemUtils::GetFileList(filePaths, fileExtensions, dirFileList);

	ProtoParser parser(filePath);
	for (const auto& [dir, fileList] : dirFileList)
	{
		for (const auto& file : fileList)
		{
			if (!parser.Load(file))
			{
				continue;
			}

			std::cout << file.string() << std::endl;
		}
	}

	auto p1 = parser.GetMessageDefineInfo("combat.CombatEvent");
	if (nullptr != p1)
	{
		
	}

	return 0;
}