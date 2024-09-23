#pragma once

#include "Common.h"
#include "BattleConfig.h"

#include "spdlog/spdlog.h"

namespace zeus
{

	class BATTLE_API StringUtils
	{
	public:

		template <typename T, template <typename, typename = std::allocator<T>> class Container = std::vector>
		static Container<T> SplitToSequence(const std::string& str, const std::string& delimiter = ",")
		{
			Container<T> result;
			size_t start = 0;
			size_t end = str.find(delimiter);
			while (end != std::string::npos)
			{
				std::istringstream iss(str.substr(start, end - start));
				T value;
				iss >> value;
				if (!iss.fail())
				{
					result.insert(result.end(), value);
				}
				start = end + delimiter.length();
				end = str.find(delimiter, start);
			}
			std::istringstream iss(str.substr(start));
			T value;
			iss >> value;
			if (!iss.fail())
			{
				result.insert(result.end(), value);
			}
			return result;
		}

		template <template <typename, typename = std::allocator<std::string>> class Container = std::vector>
		static Container<std::string> SplitToSequence(const std::string& str, const std::string& delimiter)
		{
			std::vector<std::string> result;
			size_t start = 0;
			size_t end = str.find(delimiter);
			while (end != std::string::npos)
			{
				result.insert(result.end(), str.substr(start, end - start));
				start = end + delimiter.length();
				end = str.find(delimiter, start);
			}
			const std::string lastToken = str.substr(start);
			if (!lastToken.empty())
			{
				result.insert(result.end(), lastToken);
			}
			return result;
		}

		template <typename T>
		static std::set<T> SplitToSet(const std::string& str, const std::string& delimiter = ",")
		{
			std::set<T> result;
			size_t start = 0;
			size_t end = str.find(delimiter);
			while (end != std::string::npos)
			{
				std::istringstream iss(str.substr(start, end - start));
				T value;
				iss >> value;
				if (!iss.fail())
				{
					result.insert(value);
				}
				start = end + delimiter.length();
				end = str.find(delimiter, start);
			}
			std::istringstream iss(str.substr(start));
			T value;
			iss >> value;
			if (!iss.fail())
			{
				result.insert(value);
			}
			return result;
		}

		template <>
		static std::set<std::string> SplitToSet(const std::string& str, const std::string& delimiter)
		{
			std::set<std::string> result;
			size_t start = 0;
			size_t end = str.find(delimiter);
			while (end != std::string::npos)
			{
				result.insert(str.substr(start, end - start));
				start = end + delimiter.length();
				end = str.find(delimiter, start);
			}
			const std::string lastToken = str.substr(start, end - start);
			if (!lastToken.empty())
			{
				result.insert(lastToken);
			}
			return result;
		}

		template <typename Key, typename Value>
		static std::map<Key, Value> SplitToMap(const std::string& str, const std::string& delimiter = "|,")
		{
			std::map<Key, Value> result;
			if (str.empty())
			{
				return result;
			}
			if (2 != delimiter.size())
			{
				return result;
			}
			auto splitItems = SplitToSequence<std::string>(str, std::string(1, delimiter[0]));
			for (auto item : splitItems)
			{
				auto splitKeyValue = SplitToSequence<std::string>(item, std::string(1, delimiter[1]));
				if (2 != splitKeyValue.size())
				{
					continue;
				}
				std::stringstream convertorKey(splitKeyValue[0]);
				Key key;
				convertorKey >> key;
				if (convertorKey.fail())
				{
					continue;
				}
				std::stringstream convertorValue(splitKeyValue[1]);
				Value value;
				convertorValue >> value;
				if (convertorValue.fail())
				{
					continue;
				}
				result[key] = value;
			}

			return result;
		}
		
		template <typename... Args>
		static std::string Format(const std::string& formatter, Args&&... args)
		{
			return spdlog::fmt_lib::format(spdlog::fmt_lib::runtime(formatter), std::forward<Args>(args)...);
		}

		static std::string ToUpper(const std::string& str);

		static std::string ToLower(const std::string& str);

		static std::string TrimLeft(const std::string& str);

		static std::string TrimRight(const std::string& str);

		static std::string Trim(const std::string& str);
	};

} // namespace zeus