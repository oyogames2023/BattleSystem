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

	std::string StringUtils::TrimLeft(const std::string& str)
	{
		std::string result = str;
		result.erase(result.begin(), std::find_if(result.begin(), result.end()
			, [](uint8_t c) {
				return !std::isspace(c);
		}));
		return result;
	}

	std::string StringUtils::TrimRight(const std::string& str)
	{
		std::string result = str;
		result.erase(std::find_if(result.rbegin(), result.rend()
			, [](uint8_t c) {
				return !std::isspace(c);
		}).base(), result.end());
		return result;
	}

	std::string StringUtils::Trim(const std::string& str)
	{
		return TrimLeft(TrimRight(str));
	}

} // namespace zeus