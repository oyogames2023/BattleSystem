#include "GameConfigParser.h"
#include "FilesystemUtils.h"
#include "StringUtils.h"
#include "ProtoUtils.h"

#include "xlnt/xlnt.hpp"

namespace zeus
{

	std::map<std::string, ExcelWorksheet::EExportMode> ExcelWorksheet::exportModes_ = {
		{ "all", ExcelWorksheet::EExportMode::All},
		{ "client", ExcelWorksheet::EExportMode::Client},
		{ "server", ExcelWorksheet::EExportMode::Server},
	};

	bool ExcelWorksheet::Load(const xlnt::worksheet& ws, const size_t index)
	{
		try
		{
			rows_.clear();
			title_ = ws.title();
			index_ = index;

			for (const auto& row : ws.rows())
			{
				Row columns;

				for (const auto& column : row)
				{
					columns.push_back(column.to_string());
				}

				rows_.push_back(columns);
			}

			rowCount_ = rows_.size();
			columnCount_ = ws.columns().length();
		}
		catch (const std::exception& e)
		{
			return false;
		}
		return true;
	}

	const ExcelWorksheet::Row ExcelWorksheet::GetRow(const size_t row) const
	{
		if (row >= GetRowCount())
		{
			return {};
		}
		return rows_[row];
	}

	const ExcelWorksheet::Column ExcelWorksheet::GetColumn(const size_t row, const size_t col) const
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

	size_t ExcelWorksheet::GetRowCount() const
	{
		return rowCount_;
	}

	size_t ExcelWorksheet::GetColumnCount() const
	{
		return columnCount_;
	}

	const std::string ExcelWorksheet::GetTitle() const
	{
		return title_;
	}

	size_t ExcelWorksheet::GetIndex() const
	{
		return index_;
	}

	const ExcelWorksheet::EExportMode ExcelWorksheet::GetColumnExportMode(const std::string& exportMode) const
	{
		const auto mode = StringUtils::ToLower(exportMode);
		auto it = exportModes_.find(mode);
		if (exportModes_.end() == it)
		{
			return ExcelWorksheet::EExportMode::None;
		}
		return it->second;
	}

	bool ExcelWorksheet::IsIgnoreColumn(const size_t row, const size_t col) const
	{
		const auto mode = GetColumnExportMode(GetColumn(row, col));
		return mode == ExcelWorksheet::EExportMode::None;
	}

	bool ExcelParser::Load(const fs::path& path)
	{
		if (!FilesystemUtils::IsRegularFile(path))
		{
			return false;
		}

		path_ = path;
		return Reload();
	}

	bool ExcelParser::Reload()
	{
		try
		{
			xlnt::workbook wb;
			wb.load(path_);

			const size_t size = wb.sheet_count();

			for (size_t i = 0; i < size; ++i)
			{
				ExcelWorksheetPtr ws = std::make_shared<ExcelWorksheet>();
				if (!ws->Load(wb.sheet_by_index(i), i))
				{
					return false;
				}
				worksheetByIndex_[ws->GetIndex()] = ws;
				worksheetByTitle_[ws->GetTitle()] = ws;
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

	const ExcelWorksheetPtr ExcelParser::GetWorksheetByIndex(const size_t index) const
	{
		auto it = worksheetByIndex_.find(index);
		if (worksheetByIndex_.end() == it)
		{
			return nullptr;
		}
		return it->second;
	}

	const ExcelWorksheetPtr ExcelParser::GetWorksheetByTitle(const std::string& title) const
	{
		auto it = worksheetByTitle_.find(title);
		if (worksheetByTitle_.end() == it)
		{
			return nullptr;
		}
		return it->second;
	}

	const std::vector<ExcelWorksheetPtr> ExcelParser::GetWorksheets() const
	{
		std::vector<ExcelWorksheetPtr> worksheets;
		for (const auto& [_, ws] : worksheetByIndex_)
		{
			worksheets.push_back(ws);
		}
		return worksheets;
	}

	bool GenerateHeader(const GameConfigGeneratorPtr generator, const ProtoGenerator::WorksheetFields& ws, const fs::path& outputPath)
	{
		if (nullptr == generator)
		{
			return false;
		}
		fs::create_directories(outputPath);
		std::ofstream os(outputPath / (ws.Name + ".h"));
		if (os.fail())
		{
			return false;
		}

		generator->AddPragmaOnce(os);
		generator->AddNewLine(os, 2);
		os << "#include \"Forward.h\"";
		generator->AddNewLine(os, 2);
		generator->AddNamespaceBegin(os, "zeus::config");
		generator->AddNewLineAndTab(os, 2);
		os << "namespace fs = std::filesystem;";
		generator->AddNewLine(os, 2);
		generator->AddClassForwardDeclaration(os, ws.Name);
		generator->AddNewLineAndTab(os, 2);

		// 类定义
		os << "class " << ws.Name;
		generator->AddNewLineAndTab(os, 1);
		os << "{";
		generator->AddNewLineAndTab(os, 1);
		// 声明方法
		os << "public:";
		generator->AddNewLineAndTab(os, 2, 2);
		os << "bool Load(const fs::path& path) const;";
		generator->AddNewLineAndTab(os, 2, 2);

		generator->AddNewLineAndTab(os, 2);

		// 声明成员变量
		os << "private:";
		generator->AddNewLineAndTab(os, 2);
		os << "};";
		generator->AddNewLine(os);
		generator->AddNamespaceEnd(os, "zeus::config");
		generator->AddNewLine(os, 2);


		return true;
	}

	bool GeneratorCpp(const GameConfigGeneratorPtr generator, const ProtoGenerator::WorksheetFields& ws, const fs::path& outputPath)
	{
		if (nullptr == generator)
		{
			return false;
		}
		return true;
	}

	bool GameConfigGenerator::GenerateConfigParser(const ProtoParserPtr protoParser, const ProtoGeneratorPtr protoGenerator
		, const fs::path& outputPath)
	{
		if (nullptr == protoParser || nullptr == protoGenerator)
		{
			return false;
		}

		const auto worksheets = protoGenerator->GetWorksheets();
		for (const auto& ws : worksheets)
		{
			if (!GenerateHeader(shared_from_this(), ws, outputPath))
			{
				return false;
			}
			if (!GeneratorCpp(shared_from_this(), ws, outputPath))
			{
				return false;
			}
		}

		return true;
	}

	void GameConfigGenerator::AddPragmaOnce(std::ofstream& os)
	{
		os << "#pragma once";
	}

	void GameConfigGenerator::AddNewLine(std::ofstream& os, const size_t count)
	{
		for (size_t i = 0; i < count; ++i)
		{
			os << "\n";
		}
	}

	void GameConfigGenerator::AddTab(std::ofstream& os, const size_t count)
	{
		for (size_t i = 0; i < count; ++i)
		{
			os << "\t";
		}
	}

	void GameConfigGenerator::AddNewLineAndTab(std::ofstream& os, const size_t newLineCount, const size_t tabCount)
	{
		AddNewLine(os, newLineCount);
		AddTab(os, tabCount);
	}

	void GameConfigGenerator::AddNamespaceBegin(std::ofstream& os, const std::string& name)
	{
		os << "namespace " << name;
		AddNewLine(os);
		os << "{";
	}

	void GameConfigGenerator::AddNamespaceEnd(std::ofstream& os, const std::string& name)
	{
		os << "}" << " // namespace " << name;
	}

	void GameConfigGenerator::AddClassForwardDeclaration(std::ofstream& os, const std::string& className)
	{
		AddTab(os);
		os << "class " << className << ";";
		AddNewLine(os);
		AddTab(os);
		os << "using " << className << "Ptr = std::shared_ptr<" << className << ">;";
	}

} // namespace zeus