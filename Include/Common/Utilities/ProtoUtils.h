#pragma once

#include "Forwards.h"
#include "BattleConfig.h"

#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/descriptor.h>

namespace zeus
{
	namespace fs = std::filesystem;

	struct BATTLE_API EnumerationFieldInfo
	{
		std::string Name;
		int32_t Value;
	};

	struct BATTLE_API EnumerationDefineInfo
	{
		std::string Name;
		std::string FullName;
		std::string PackageName;
		std::vector<EnumerationFieldInfo> Fields;
		fs::path FilePath;
	};

	struct BATTLE_API ProtoFieldInfo
	{
		std::string Name;
		google::protobuf::internal::FieldDescriptorLite::Type ProtoType;
		std::string DataType;
	};

	struct BATTLE_API MessageDefineInfo
	{
		std::string Name; // Message or Enumeration Ãû³Æ
		std::string FullName; // Message or Enumeration Ãû³Æ
		std::string PackageName;
		std::vector<ProtoFieldInfo> Fields;
		std::vector<MessageDefineInfoPtr> NestedDefines;
		std::vector<std::string> Enumerations;
		fs::path FilePath;
	};

	class BATTLE_API ProtoErrorCollector
		: public google::protobuf::compiler::MultiFileErrorCollector
	{
	public:

		void RecordError(absl::string_view filename, int line, int column, absl::string_view message) override;
	};

	class BATTLE_API ProtoParser
	{
	public:

		ProtoParser(const fs::path& searchPath);

		virtual ~ProtoParser();

	public:

		bool Load(const fs::path& filePath);

		const MessageDefineInfoPtr GetMessageDefineInfo(const std::string& name) const;

		const EnumerationDefineInfoPtr GetEnumerationDefineInfo(const std::string& name) const;

		bool IsMessage(const std::string& name) const;

		bool IsEnumeration(const std::string& name) const;

		fs::path GetFilePath(const std::string& name) const;

	private:

		void Reset();

		void ParseMessages(const google::protobuf::FileDescriptor* fileDescriptor
			, const fs::path& filePath);

		void ParseMessage(const google::protobuf::Descriptor* descriptor, const fs::path& filePath
			, MessageDefineInfoPtr parent = nullptr);

		void ParseEnumerations(const google::protobuf::FileDescriptor* fileDescriptor, const fs::path& filePath);

		void ParseEnumeration(const google::protobuf::EnumDescriptor* enumDescriptor, const fs::path& filePath);

	private:

		fs::path searchPath_;

		google::protobuf::compiler::DiskSourceTree sourceTree_;

		ProtoErrorCollector errorCollector_;

		google::protobuf::compiler::Importer* importer_ = nullptr;

		std::unordered_map<std::string, MessageDefineInfoPtr> parsedMessages_;

		std::unordered_map<std::string, EnumerationDefineInfoPtr> parsedEnumerations_;

		std::unordered_set<std::string> parsedFiles_;
	};

	class BATTLE_API ProtoGenerator
	{
	public:

		enum class EDataType : uint32_t
		{
			Unknown,
			Int32,
			Int64,
			UInt32,
			UInt64,
			String,
			Double,
			Float,
			Boolean,

			Message,
			Enumeration,

			Vector,
			Map,

			Max,
		};

		struct BATTLE_API FieldInfo
		{
			std::string Name;
			EDataType DataType = EDataType::Unknown;
			std::string KeyDataType;
			std::string ValueDataType;
			std::string Comment;
		};

		struct BATTLE_API WorksheetFields
		{
			std::string Name;
			std::string PackageName;
			fs::path Path;
			std::vector<FieldInfo> Fields;
		};

	public:

		ProtoGenerator(const std::string& packageName = "");

	public:

		bool ParseWorksheets(const ExcelParserPtr excelParser, const ProtoParserPtr protoParser
			, const fs::path& outputPath);

		const std::vector<ProtoGenerator::WorksheetFields> GetWorksheets() const;

		const std::string GetPackageName() const;

	public:

		static std::string GetProtoDataType(const ProtoGenerator::EDataType dataType);

		static bool IsPod(const std::string& dataType);

		static bool IsPod(const ProtoGenerator::EDataType dataType);

		static ProtoGenerator::EDataType GetDataType(const std::string& dataType, const ProtoParserPtr protoParser);

		static std::pair<std::string, std::string> GetKeyDataTypeAndValueDataType(const std::string& dataType);

	private:

		bool GenerateFile(const std::vector<WorksheetFields>& worksheetFields, const fs::path& outputPath
			, const ProtoParserPtr protoParser);

		void AddProtoVersion(std::ofstream& os, const std::string& version);

		void AddNewLine(std::ofstream& os, const size_t count = 1);

		void AddTab(std::ofstream& os, const size_t count = 1);

		void AddImportProto(std::ofstream& os, const fs::path& path);

		void AddMessage(std::ofstream& os, const WorksheetFields& ws);

		void AddPackage(std::ofstream& os, const std::string& name);

	private:

		static std::map<ProtoGenerator::EDataType, std::string> dataTypeToProtoDataType_;

		static std::map<std::string, ProtoGenerator::EDataType> pods_;

		std::vector<ProtoGenerator::WorksheetFields> worksheetFields_;

		std::string packageName_;
	};

} // namespace zeus