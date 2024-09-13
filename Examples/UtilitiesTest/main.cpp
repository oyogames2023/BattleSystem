#include "StringUtils.h"
#include "FilesystemUtils.h"

int main(int argc, char* argv[])
{
	namespace fs = std::filesystem;

	fs::path logDir;

	logDir /= zeus::StringUtils::Format("{:04}-{:02}", 2024, 9);

	std::cout << logDir.string() << std::endl;

	std::cout << zeus::FilesystemUtils::GetExecutableDirectory() << std::endl;

	return 0;
}