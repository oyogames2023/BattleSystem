#pragma once

#include "Forwards.h"

namespace zeus
{
	namespace fs = std::filesystem;

	class ExcelParser
	{
	public:

		using Column = std::string;
		using Row = std::vector<Column>;

	public:

		bool Load(const fs::path& path);

		bool Reload();

		const fs::path GetPath() const;

		size_t GetRowCount() const;

		size_t GetColumnCount() const;

		const ExcelParser::Row GetRow(const size_t row) const;

		const ExcelParser::Column GetColumn(const size_t row, const size_t col) const;

	private:

		fs::path path_;

		std::vector<Row> rows_;

		size_t rowCount_ = 0;

		size_t columnCount_ = 0;
	};

	class GameConfigGenerator
	{
	public:

		enum class ERowInfo : uint32_t
		{
			FieldName, // 字段名称
			DataType, // 数据类型
			ExportMode, // 导出方式
			FieldComment, // 字段描述
			InvalidMaxRows, // 有效数据行数
		};

	public:

		bool GenerateProto(const ExcelParserPtr parser);
	};

} // namespace zeus