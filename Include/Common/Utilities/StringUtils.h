#pragma once

#include "Commom.h"

#include "spdlog/spdlog.h"

namespace zeus
{

	class  StringUtils
	{
	public:
		
		template <typename... Args>
		static std::string Format(const std::string& formatter, Args&&... args)
		{
			return spdlog::fmt_lib::format(spdlog::fmt_lib::runtime(formatter), std::forward<Args>(args)...);
		}
	};

} // namespace zeus