#include "GameConfigParser.h"
#include "FilesystemUtils.h"

#include "xlnt/xlnt.hpp"

namespace zeus
{

	bool ExcelParser::Load(const fs::path& path)
	{
		if (!FilesystemUtils::IsRegularFile(path))
		{
			return false;
		}

		try
		{
			path_ = path;
			rows_.clear();
			xlnt::workbook wb;
			wb.load(path);
			const auto ws = wb.active_sheet();

			for (const auto& row : ws.rows())
			{
				Row columns;

				for (const auto& column : row)
				{
					columns.push_back(column.to_string());
				}

				rows_.push_back(columns);
			}
		}
		catch (const std::exception& e)
		{
			return false;
		}

		return true;
	}

	const fs::path ExcelParser::GetPath() const
	{
		return path_;
	}

	size_t ExcelParser::GetRowCount() const
	{
		return rowCount_;
	}

	size_t ExcelParser::GetColumnCount() const
	{
		return columnCount_;
	}

	const ExcelParser::Row ExcelParser::GetRow(const size_t row) const
	{
		if (row >= GetRowCount())
		{
			return {};
		}
		return rows_[row];
	}

	const ExcelParser::Column ExcelParser::GetColumn(const size_t row, const size_t col) const
	{
		if (row >= GetRowCount())
		{
			return {};
		}
		if (col >= GetColumnCount())
		{
			return {};
		}
		return rows_[row][col];
	}

	bool GameConfigGenerator::GenerateProto(const ExcelParser& parser)
	{
		return true;
	}

} // namespace zeus