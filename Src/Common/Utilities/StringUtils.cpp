#include "StringUtils.h"

namespace zeus
{

	std::string StringUtils::ToUpper(const std::string& str)
	{
		std::string result = str;
		std::transform(result.begin(), result.end(), result.begin()
			, [](uint8_t c) {
				return std::toupper(c);
			});
		return result;
	}

	std::string StringUtils::ToLower(const std::string& str)
	{
		std::string result = str;
		std::transform(result.begin(), result.end(), result.begin()
			, [](uint8_t c) {
				return std::tolower(c);
		});
		return result;
	}

} // namespace zeus