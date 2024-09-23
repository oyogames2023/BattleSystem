#pragma once

#include "Forwards.h"
#include "BattleConfig.h"

#include "xlnt/xlnt.hpp"

namespace zeus
{
	namespace fs = std::filesystem;

	class BATTLE_API ExcelWorksheet
	{
	public:

		enum class ERowInfo : uint32_t
		{
			FieldName, // 字段名称
			DataType, // 数据类型
			ExportMode, // 导出方式
			FieldComment, // 字段描述
			MinimumRequiredRows, // 最少需要行数
		};

		enum class EExportMode : uint32_t
		{
			None,
			All,
			Client,
			Server,
		};

		using Column = std::string;
		using Row = std::vector<Column>;

	public:

		bool Load(const xlnt::worksheet& ws, const size_t index);

		const ExcelWorksheet::Row GetRow(const size_t row) const;

		const ExcelWorksheet::Column GetColumn(const size_t row, const size_t col) const;

		size_t GetRowCount() const;

		size_t GetColumnCount() const;

		const std::string GetTitle() const;

		size_t GetIndex() const;

		const ExcelWorksheet::EExportMode GetColumnExportMode(const std::string& exportMode) const;

		bool IsIgnoreColumn(const size_t row, const size_t col) const;

	private:

		std::string title_;

		size_t index_ = 0;

		std::vector<Row> rows_;

		size_t rowCount_ = 0;

		size_t columnCount_ = 0;

		static std::map<std::string, ExcelWorksheet::EExportMode> exportModes_;
	};

	class BATTLE_API ExcelParser
	{
	public:

		bool Load(const fs::path& path);

		bool Reload();

		const fs::path GetPath() const;

		const ExcelWorksheetPtr GetWorksheetByIndex(const size_t index) const;

		const ExcelWorksheetPtr GetWorksheetByTitle(const std::string& title) const;

		const std::vector<ExcelWorksheetPtr> GetWorksheets() const;

	private:

		fs::path path_;

		std::map<uint32_t, ExcelWorksheetPtr> worksheetByIndex_;

		std::map<std::string, ExcelWorksheetPtr> worksheetByTitle_;
	};

	class BATTLE_API GameConfigGenerator
		: public std::enable_shared_from_this<GameConfigGenerator>
	{
	public:

		bool GenerateConfigParser(const ProtoParserPtr protoParser, const ProtoGeneratorPtr protoGenerator
			, const fs::path& outputPath);

		void AddPragmaOnce(std::ofstream& os);

		void AddNewLine(std::ofstream& os, const size_t count = 1);

		void AddTab(std::ofstream& os, const size_t count = 1);

		void AddNewLineAndTab(std::ofstream& os, const size_t newLineCount = 1, const size_t tabCount = 1);

		void AddNamespaceBegin(std::ofstream& os, const std::string& name);

		void AddNamespaceEnd(std::ofstream& os, const std::string& name);

		void AddClassForwardDeclaration(std::ofstream& os, const std::string& className);
	};

} // namespace zeus