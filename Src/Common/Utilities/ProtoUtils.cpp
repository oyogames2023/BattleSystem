#include "ProtoUtils.h"

namespace zeus
{

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
		ParseMessages(fileDescriptor);
		ParseEnumerations(fileDescriptor);

		return true;
	}

	const ProtoDefineInfoPtr ProtoParser::GetProtoDefineInfo(const std::string& name) const
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

	void ProtoParser::Reset()
	{
		if (nullptr != importer_)
		{
			delete importer_;
			importer_ = nullptr;
		}

		google::protobuf::ShutdownProtobufLibrary();
	}

	void ProtoParser::ParseMessages(const google::protobuf::FileDescriptor* fileDescriptor)
	{
		if (nullptr == fileDescriptor)
		{
			return;
		}
		const auto size = fileDescriptor->message_type_count();
		for (int32_t i = 0; i < size; ++i)
		{
			ParseMessage(fileDescriptor->message_type(i));
		}
	}

	void ProtoParser::ParseMessage(const google::protobuf::Descriptor* descriptor, ProtoDefineInfoPtr parent)
	{
		if (nullptr == descriptor)
		{
			return;
		}

		ProtoDefineInfoPtr info = std::make_shared<ProtoDefineInfo>();
		info->Name = descriptor->name();
		info->FullName = descriptor->full_name();

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
			ParseMessage(descriptor->nested_type(i), info);
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

	void ProtoParser::ParseEnumerations(const google::protobuf::FileDescriptor* fileDescriptor)
	{
		if (nullptr == fileDescriptor)
		{
			return;
		}

		const auto size = fileDescriptor->enum_type_count();
		for (int32_t i = 0; i < size; ++i)
		{
			ParseEnumeration(fileDescriptor->enum_type(i));
		}
	}

	void ProtoParser::ParseEnumeration(const google::protobuf::EnumDescriptor* enumDescriptor)
	{
		if (nullptr == enumDescriptor)
		{
			return;
		}
		EnumerationDefineInfoPtr info = std::make_shared<EnumerationDefineInfo>();
		info->Name = enumDescriptor->name();
		info->FullName = enumDescriptor->full_name();
		const auto size = enumDescriptor->value_count();
		for (int32_t i = 0; i < size; ++i)
		{
			const auto valueDescriptor = enumDescriptor->value(i);
			info->Fields.push_back({valueDescriptor->name(), valueDescriptor->number()});
		}
		parsedEnumerations_[info->FullName] = info;
	}

} // namespace zeuss