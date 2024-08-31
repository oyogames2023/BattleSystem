#include "Commom.h"
#include "DateTime.h"
#include "TimeUtils.h"

using namespace zeus;

int main(int argc, char* argv[])
{
	DateTime dt;
	std::cout << dt.ToString() << std::endl;
	std::cout << dt.GetCurrentSeconds() << std::endl;
	std::cout << TimeUtils::FormatYearMonth(2024, 8) << std::endl;
	std::cout << DateTime(1725130580).ToString() << std::endl;
	std::cout << TimeUtils::ValidateDateTime(2023, 2, 29) << std::endl;

	return 0;
}