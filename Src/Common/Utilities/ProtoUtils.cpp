#include "ProtoUtils.h"
#include "GameConfigParser.h"
#include "StringUtils.h"
#include "FilesystemUtils.h"

namespace zeus
{

	std::map<ProtoGenerator::EDataType, std::string> ProtoGenerator::dataTypeToProtoDataType_ = {
		{ EDataType::Int32, "int32" }, { EDataType::UInt32, "uint32" },
		{ EDataType::Int64, "int64" }, { EDataType::UInt64, "uint64" },
		{ EDataType::Double, "double" }, { EDataType::Float, "float" },
		{ EDataType::Boolean, "bool" }, { EDataType::String, "string" },
		{ EDataType::Map, "map" },
	};

	std::map<std::string, ProtoGenerator::EDataType> ProtoGenerator::pods_ = {
		{ "int32", EDataType::Int32 }, { "uint32", EDataType::UInt32 },
		{ "int64", EDataType::Int64 }, { "uint64", EDataType::UInt64 },
		{ "double", EDataType::Double }, { "float", EDataType::Float },
		{ "bool", EDataType::Boolean }, { "string", EDataType::String },
	};

	void ProtoErrorCollector::RecordError(absl::string_view filename, int line, int column, absl::string_view message)
	{
		std::cerr << "Error in " << filename << " at " << line << ":" << column << " -> " << message << std::endl;
	}

	ProtoParser::ProtoParser(const fs::path& searchPath)
		: searchPath_(searchPath)
	{
		searchPath_ = searchPath;
		sourceTree_.MapPath("", searchPath.generic_string());
		importer_ = new google::protobuf::compiler::Importer(&sourceTree_, &errorCollector_);
	}

	ProtoParser::~ProtoParser()
	{
		Reset();
	}

	bool ProtoParser::Load(const fs::path& filePath)
	{
		const auto genericPath = filePath.generic_string();
		if (parsedFiles_.find(genericPath) != parsedFiles_.end())
		{
			return false;
		}
		const google::protobuf::FileDescriptor* fileDescriptor = importer_->Import(genericPath);
		if (nullptr == fileDescriptor)
		{
			return false;
		}
		parsedFiles_.insert(genericPath);
		ParseMessages(fileDescriptor, filePath);
		ParseEnumerations(fileDescriptor, filePath);

		return true;
	}

	const MessageDefineInfoPtr ProtoParser::GetMessageDefineInfo(const std::string& name) const
	{
		auto it = parsedMessages_.find(name);
		if (parsedMessages_.end() == it)
		{
			return nullptr;
		}
		return it->second;
	}

	const EnumerationDefineInfoPtr ProtoParser::GetEnumerationDefineInfo(const std::string& name) const
	{
		auto it = parsedEnumerations_.find(name);
		if (parsedEnumerations_.end() == it)
		{
			return nullptr;
		}
		return it->second;
	}

	bool ProtoParser::IsMessage(const std::string& name) const
	{
		return GetMessageDefineInfo(name) != nullptr;
	}

	bool ProtoParser::IsEnumeration(const std::string& name) const
	{
		return GetEnumerationDefineInfo(name) != nullptr;
	}

	fs::path ProtoParser::GetFilePath(const std::string& name) const
	{
		const auto enumDefine = GetEnumerationDefineInfo(name);
		if (nullptr != enumDefine)
		{
			return enumDefine->FilePath;
		}
		const auto messageDefine = GetMessageDefineInfo(name);
		if (nullptr != messageDefine)
		{
			return messageDefine->FilePath;
		}

		return { "" };
	}

	void ProtoParser::Reset()
	{
		if (nullptr != importer_)
		{
			delete importer_;
			importer_ = nullptr;
		}

		google::protobuf::ShutdownProtobufLibrary();
	}

	void ProtoParser::ParseMessages(const google::protobuf::FileDescriptor* fileDescriptor, const fs::path& filePath)
	{
		if (nullptr == fileDescriptor)
		{
			return;
		}
		const auto size = fileDescriptor->message_type_count();
		for (int32_t i = 0; i < size; ++i)
		{
			ParseMessage(fileDescriptor->message_type(i), filePath);
		}
	}

	void ProtoParser::ParseMessage(const google::protobuf::Descriptor* descriptor, const fs::path& filePath
		, MessageDefineInfoPtr parent)
	{
		if (nullptr == descriptor)
		{
			return;
		}

		MessageDefineInfoPtr info = std::make_shared<MessageDefineInfo>();
		info->Name = descriptor->name();
		info->FullName = descriptor->full_name();
		info->PackageName = descriptor->file()->package();
		info->FilePath = filePath;

		for (int32_t i = 0; i < descriptor->field_count(); ++i)
		{
			const auto field = descriptor->field(i);
			if (field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE)
			{
				info->Fields.push_back({ field->name(), field->type(), field->message_type()->full_name() });
			}
			else
			{
				info->Fields.push_back({ field->name(), field->type(), field->type_name() });
			}
		}

		for (int32_t i = 0; i < descriptor->enum_type_count(); ++i)
		{
			info->Enumerations.push_back(descriptor->enum_type(i)->name());
		}

		for (int32_t i = 0; i < descriptor->nested_type_count(); ++i)
		{
			ParseMessage(descriptor->nested_type(i), filePath, info);
		}

		if (nullptr != parent)
		{
			parent->NestedDefines.push_back(info);
		}
		else
		{
			parsedMessages_[info->FullName] = info;
		}
	}

	void ProtoParser::ParseEnumerations(const google::protobuf::FileDescriptor* fileDescriptor, const fs::path& filePath)
	{
		if (nullptr == fileDescriptor)
		{
			return;
		}

		const auto size = fileDescriptor->enum_type_count();
		for (int32_t i = 0; i < size; ++i)
		{
			ParseEnumeration(fileDescriptor->enum_type(i), filePath);
		}
	}

	void ProtoParser::ParseEnumeration(const google::protobuf::EnumDescriptor* enumDescriptor, const fs::path& filePath)
	{
		if (nullptr == enumDescriptor)
		{
			return;
		}
		EnumerationDefineInfoPtr info = std::make_shared<EnumerationDefineInfo>();
		info->Name = enumDescriptor->name();
		info->FullName = enumDescriptor->full_name();
		info->PackageName = enumDescriptor->file()->package();
		info->FilePath = filePath;
		const auto size = enumDescriptor->value_count();
		for (int32_t i = 0; i < size; ++i)
		{
			const auto valueDescriptor = enumDescriptor->value(i);
			info->Fields.push_back({valueDescriptor->name(), valueDescriptor->number()});
		}
		parsedEnumerations_[info->FullName] = info;
	}

	ProtoGenerator::ProtoGenerator(const std::string& packageName)
		: packageName_(packageName)
	{
	}

	bool ProtoGenerator::ParseWorksheets(const ExcelParserPtr excelParser, const ProtoParserPtr protoParser
		, const fs::path& outputPath)
	{
		if (nullptr == excelParser || nullptr == protoParser)
		{
			return false;
		}

		const auto worksheets = excelParser->GetWorksheets();
		for (const auto ws : worksheets)
		{
			const auto minimumRequiredRows = static_cast<uint32_t>(ExcelWorksheet::ERowInfo::MinimumRequiredRows);
			if (minimumRequiredRows > ws->GetRowCount())
			{
				return false;
			}

			WorksheetFields worksheet;
			worksheet.Name = ws->GetTitle();
			worksheet.Path = outputPath;
			std::set<std::string> fieldNames;
			const size_t columnMaxSize = ws->GetColumnCount();
			for (size_t col = 0; col < columnMaxSize; ++col)
			{
				if (ws->IsIgnoreColumn(static_cast<size_t>(ExcelWorksheet::ERowInfo::ExportMode), col))
				{
					continue;
				}

				const auto dataType = ws->GetColumn(static_cast<size_t>(ExcelWorksheet::ERowInfo::DataType), col);
				const auto keyDataTypeAndValueDataType = GetKeyDataTypeAndValueDataType(dataType);
				FieldInfo field;
				field.Name = ws->GetColumn(static_cast<size_t>(ExcelWorksheet::ERowInfo::FieldName), col);
				field.Comment = ws->GetColumn(static_cast<size_t>(ExcelWorksheet::ERowInfo::FieldComment), col);
				field.DataType = GetDataType(dataType, protoParser);
				field.KeyDataType = keyDataTypeAndValueDataType.first;
				field.ValueDataType = keyDataTypeAndValueDataType.second;

				if (ProtoGenerator::EDataType::Unknown == field.DataType)
				{
					return false;
				}
				else if (ProtoGenerator::EDataType::Vector == field.DataType)
				{
					if (!protoParser->IsMessage(field.ValueDataType))
					{
						return false;
					}
				}
				else if (ProtoGenerator::EDataType::Map == field.DataType)
				{
					if (!IsPod(field.KeyDataType) && !protoParser->IsEnumeration(field.KeyDataType))
					{
						return false;
					}
					if (!IsPod(field.ValueDataType) && !protoParser->IsEnumeration(field.ValueDataType)
						&& !protoParser->IsMessage(field.ValueDataType))
					{
						return false;
					}
				}
				else if (ProtoGenerator::EDataType::Enumeration == field.DataType)
				{
					if (!protoParser->IsEnumeration(field.ValueDataType))
					{
						return false;
					}
				}
				else if (ProtoGenerator::EDataType::Message == field.DataType)
				{
					if (!protoParser->IsMessage(field.ValueDataType))
					{
						return false;
					}
				}

				if (fieldNames.find(field.Name) != fieldNames.end())
				{
					return false;
				}

				fieldNames.insert(field.Name);
				worksheet.Fields.push_back(field);
			}

			worksheetFields_.push_back(worksheet);
		}

		return GenerateFile(worksheetFields_, outputPath, protoParser);
	}

	const std::vector<ProtoGenerator::WorksheetFields> ProtoGenerator::GetWorksheets() const
	{
		return worksheetFields_;
	}

	const std::string ProtoGenerator::GetPackageName() const
	{
		return packageName_;
	}

	std::string ProtoGenerator::GetProtoDataType(const ProtoGenerator::EDataType dataType)
	{
		auto it = dataTypeToProtoDataType_.find(dataType);
		if (dataTypeToProtoDataType_.end() == it)
		{
			return {};
		}
		return it->second;
	}

	bool ProtoGenerator::IsPod(const std::string& dataType)
	{
		const auto lowerLiteral = StringUtils::ToLower(dataType);
		return (pods_.find(lowerLiteral) != pods_.end());
	}

	bool ProtoGenerator::IsPod(const ProtoGenerator::EDataType dataType)
	{
		static const std::set<ProtoGenerator::EDataType> pods = {
			ProtoGenerator::EDataType::Int32, ProtoGenerator::EDataType::UInt32,
			ProtoGenerator::EDataType::Int64, ProtoGenerator::EDataType::UInt64,
			ProtoGenerator::EDataType::Float, ProtoGenerator::EDataType::Double,
			ProtoGenerator::EDataType::String, ProtoGenerator::EDataType::Boolean,
		};

		return (pods.find(dataType) != pods.end());
	}

	ProtoGenerator::EDataType ProtoGenerator::GetDataType(const std::string& dataType, const ProtoParserPtr protoParser)
	{
		if (nullptr == protoParser)
		{
			return ProtoGenerator::EDataType::Unknown;
		}

		const auto lowerLiteral = dataType;
		auto it = pods_.find(StringUtils::ToLower(lowerLiteral));
		if (pods_.end() != it)
		{
			return it->second;
		}

		std::regex containerRegex(R"(std::([a-zA-Z_]+)<(.+)>$)");
		std::smatch match;

		if (std::regex_search(lowerLiteral, match, containerRegex))
		{
			const std::string containerType = match[1];
			const std::string templateParam = match[2];
			if ("vector" == containerType)
			{
				return EDataType::Vector;
			}
			else if ("map" == containerType)
			{
				return EDataType::Map;
			}
		}
		else
		{
			if (protoParser->IsEnumeration(lowerLiteral))
			{
				return EDataType::Enumeration;
			}
			else if (protoParser->IsMessage(lowerLiteral))
			{
				return EDataType::Message;
			}
		}

		return ProtoGenerator::EDataType::Unknown;
	}

	std::pair<std::string, std::string> ProtoGenerator::GetKeyDataTypeAndValueDataType(const std::string& dataType)
	{
		if (IsPod(dataType))
		{
			return { "", StringUtils::ToLower(dataType) };
		}

		auto lowerLiteral = dataType;
		std::regex containerRegex(R"(std::([a-zA-Z_]+)<(.+)>$)");
		std::smatch match;

		if (!std::regex_search(lowerLiteral, match, containerRegex))
		{
			return { "", lowerLiteral };
		}

		std::string keyDataType;
		std::string valueDataType;
		const std::string containerType = match[1];
		std::string templateParams = match[2];

		if (templateParams.find(',') != std::string::npos)
		{
			std::regex mapRegex(R"((.+)\s*,\s*(.+))");
			std::smatch mapMatch;
			if (std::regex_search(templateParams, mapMatch, mapRegex))
			{
				keyDataType = mapMatch[1];
				valueDataType = mapMatch[2];
			}
		}
		else
		{
			valueDataType = templateParams;
		}

		if (IsPod(keyDataType))
		{
			keyDataType = StringUtils::ToLower(keyDataType);
		}

		if (IsPod(valueDataType))
		{
			valueDataType = StringUtils::ToLower(valueDataType);
		}

		return { keyDataType, valueDataType };
	}

	bool ProtoGenerator::GenerateFile(const std::vector<WorksheetFields>& worksheetFields, const fs::path& outputPath
		, const ProtoParserPtr protoParser)
	{
		fs::create_directories(FilesystemUtils::GetParentDirectory(outputPath));
		std::ofstream os(outputPath);
		if (os.fail())
		{
			return false;
		}

		std::set<fs::path> importProtoPaths;
		for (auto it = worksheetFields.begin(); worksheetFields.end() != it; ++it)
		{
			const auto& ws = *it;
			for (const auto& field : ws.Fields)
			{
				const auto filePath = protoParser->GetFilePath(field.ValueDataType);
				if (!filePath.empty())
				{
					importProtoPaths.insert(filePath);
				}
			}
		}

		AddProtoVersion(os, "proto3");
		AddNewLine(os, 2);
		AddPackage(os, "config");
		AddNewLine(os, 2);

		for (auto it = importProtoPaths.begin(); importProtoPaths.end() != it; ++it)
		{
			if (importProtoPaths.begin() != it)
			{
				AddNewLine(os);
			}
			const auto& filePath = *it;
			AddImportProto(os, filePath);
		}

		AddNewLine(os, 2);

		for (auto it = worksheetFields.begin(); worksheetFields.end() != it; ++it)
		{
			if (worksheetFields.begin() != it)
			{
				AddNewLine(os, 2);
			}
			const auto& ws = *it;
			AddMessage(os, ws);
		}

		os.close();

		return true;
	}

	void ProtoGenerator::AddProtoVersion(std::ofstream& os, const std::string& version)
	{
		os << "syntax = " << "\"" << version << "\"" << ";";
	}

	void ProtoGenerator::AddNewLine(std::ofstream& os, const size_t count)
	{
		for (size_t i = 0; i < count; ++i)
		{
			os << "\n";
		}
	}

	void ProtoGenerator::AddTab(std::ofstream& os, const size_t count /*= 1*/)
	{
		for (size_t i = 0; i < count; ++i)
		{
			os << "\t";
		}
	}

	void ProtoGenerator::AddImportProto(std::ofstream& os, const fs::path& path)
	{
		os << "import \"" << path.generic_string() << "\";";
	}

	void ProtoGenerator::AddMessage(std::ofstream& os, const WorksheetFields& ws)
	{
		os << "message " << ws.Name;
		AddNewLine(os);
		os << "{";
		AddNewLine(os);
		for (size_t i = 0; i < ws.Fields.size(); ++i)
		{
			if (i != 0)
			{
				AddNewLine(os);
			}
			const auto& field = ws.Fields[i];
			AddTab(os);
			if (IsPod(field.DataType) || EDataType::Enumeration == field.DataType || EDataType::Message == field.DataType)
			{
				os << field.ValueDataType << " " << field.Name << " = " << (i + 1) << ";";
			}
			else if (EDataType::Vector == field.DataType)
			{
				os << "repeated " << field.ValueDataType << " " << field.Name << " = " << (i + 1) << ";";
			}
			else if (EDataType::Map == field.DataType)
			{
				os << "map<" << field.KeyDataType << "," << field.ValueDataType << ">" << " " << field.Name << " = " << (i + 1) << ";";
			}
			
			if (!field.Comment.empty())
			{
				os << " " << "// " << field.Comment;
			}
		}
		AddNewLine(os);
		os << "}";
	}

	void ProtoGenerator::AddPackage(std::ofstream& os, const std::string& name)
	{
		if (name.empty())
		{
			return;
		}

		os << "package " << name << ";";
	}

} // namespace zeuss