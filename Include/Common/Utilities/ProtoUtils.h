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
		std::vector<EnumerationFieldInfo> Fields;
	};

	struct BATTLE_API ProtoFieldInfo
	{
		std::string Name;
		google::protobuf::internal::FieldDescriptorLite::Type DataType;
		std::string RealDataType;
	};

	struct BATTLE_API ProtoDefineInfo
	{
		std::string Name; // Message or Enumeration Ãû³Æ
		std::string FullName; // Message or Enumeration Ãû³Æ
		std::vector<ProtoFieldInfo> Fields;
		std::vector<ProtoDefineInfoPtr> NestedDefines;
		std::vector<std::string> Enumerations;
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

		const ProtoDefineInfoPtr GetProtoDefineInfo(const std::string& name) const;

		const EnumerationDefineInfoPtr GetEnumerationDefineInfo(const std::string& name) const;

	private:

		void Reset();

		void ParseMessages(const google::protobuf::FileDescriptor* fileDescriptor);

		void ParseMessage(const google::protobuf::Descriptor* descriptor, ProtoDefineInfoPtr parent = nullptr);

		void ParseEnumerations(const google::protobuf::FileDescriptor* fileDescriptor);

		void ParseEnumeration(const google::protobuf::EnumDescriptor* enumDescriptor);

	private:

		fs::path searchPath_;

		google::protobuf::compiler::DiskSourceTree sourceTree_;

		ProtoErrorCollector errorCollector_;

		google::protobuf::compiler::Importer* importer_ = nullptr;

		std::unordered_map<std::string, ProtoDefineInfoPtr> parsedMessages_;

		std::unordered_map<std::string, EnumerationDefineInfoPtr> parsedEnumerations_;

		std::unordered_set<std::string> parsedFiles_;
	};

} // namespace zeus