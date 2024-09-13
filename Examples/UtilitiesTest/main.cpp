#include "StringUtils.h"
#include "FilesystemUtils.h"

template <typename T>
void PrintVector(const std::vector<T>& container)
{
	for (const auto& element : container)
	{
		std::cout << element << " ";
	}
	std::cout << std::endl;
}

template <typename Key, typename Value>
void PrintMap(const std::map<Key, Value>& m)
{
	for (const auto& [k, v] : m)
	{
		std::cout << "key = " << k << ", " << "value = " << v << std::endl;
	}
}

template <typename T>
void PrintSet(const std::set<T>& container)
{
	for (const auto& element : container)
	{
		std::cout << element << " ";
	}
	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	namespace fs = std::filesystem;

	fs::path logDir;

	logDir /= zeus::StringUtils::Format("{:04}-{:02}", 2024, 9);

	std::cout << logDir.string() << std::endl;

	std::cout << zeus::FilesystemUtils::GetExecutableDirectory() << std::endl;

	auto v1 = zeus::StringUtils::SplitToSequence<std::string>("1,2,3");
	auto v2 = zeus::StringUtils::SplitToSequence<uint64_t>("1,2,3");
	PrintVector(v1);
	PrintVector(v2);

	auto s1 = zeus::StringUtils::SplitToSet<std::string>("1,2,3");
	auto s2 = zeus::StringUtils::SplitToSet<std::string>("1,2,3");
	PrintSet(s1);
	PrintSet(s2);

	auto m1 = zeus::StringUtils::SplitToMap<std::string, std::string>("1001,2|1002,1");
	auto m2 = zeus::StringUtils::SplitToMap<uint32_t, uint64_t>("5001,2|5002,1");
	PrintMap(m1);
	PrintMap(m2);

	return 0;
}