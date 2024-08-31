#include "JSONParser.h"

int main(int argc, char* argv[])
{
	std::vector<uint64_t> uint64Array = {
		1, 2, 3, 4, 5
	};

	std::map<std::string, int> exampleMap1 = {
		{"key1", 100},
		{"key2", 200}
	};

	std::map<std::string, int> exampleMap2 = {
		{"key3", 100},
		{"key4", 200}
	};

	zeus::JSONParser parser("");
	parser.SetArray("Quest.NeedItems", uint64Array);
	parser.AppendArray("Quest.NeedItems", uint64Array);
	parser.SetMap("Quest.Awards", exampleMap1);
	parser.AppendMap("Quest.Awards", exampleMap2);
	parser.SetString("Quest.Name", "Luke");
	parser.Save("test.json");

	return 0;
}