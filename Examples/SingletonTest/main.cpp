#include "Common.h"
#include "Singleton.h"

using namespace zeus;

class ItemManager
	: public Singleton<ItemManager>
{
public:

	bool Initialize()
	{
		std::cout << "Initialize done" << std::endl;
		return true;
	}

	void Destory()
	{
		std::cout << "Destory done" << std::endl;
	}
};

int main(int argc, char* argv[])
{
	ItemManager::GetInstance();

	return 0;
}