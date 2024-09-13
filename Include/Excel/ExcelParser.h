#pragma once

#include "Commom.h"
#include "BattleConfig.h"

//#include "xlnt/xlnt.hpp"

namespace zeus
{

	class BATTLE_API ExcelParser
	{
	public:

		bool Load(const std::string& path);

	private:

		std::string path_;
	};

} // namespace zeus