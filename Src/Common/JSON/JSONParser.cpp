#include "JSONParser.h"

namespace zeus
{

	JSONParser::JSONParser(const std::string& filename)
		: filename_(filename)
	{
	}

	bool JSONParser::Load()
	{
		std::ifstream file(filename_, std::ifstream::binary);
		Json::Reader reader;
		return reader.parse(file, root_, false);
	}

	bool JSONParser::Save(const std::string& filename)
	{
		std::ofstream file(filename, std::ofstream::binary);
		Json::StyledStreamWriter writer("  ");
		writer.write(file, root_);
		return file.good();
	}

	void JSONParser::SetInt8(const std::string& path, const int8_t value)
	{
		GetNode(path) = value;
	}

	void JSONParser::SetInt16(const std::string& path, const int16_t value)
	{
		GetNode(path) = value;
	}

	void JSONParser::SetInt32(const std::string& path, const int32_t value)
	{
		GetNode(path) = value;
	}

	void JSONParser::SetInt64(const std::string& path, const int64_t value)
	{
		GetNode(path) = value;
	}

	int8_t JSONParser::GetInt8(const std::string& path)
	{
		return static_cast<int8_t>(GetNode(path).asInt());
	}

	int16_t JSONParser::GetInt16(const std::string& path)
	{
		return static_cast<int16_t>(GetNode(path).asInt());
	}

	int32_t JSONParser::GetInt32(const std::string& path)
	{
		return GetNode(path).asInt();
	}

	int64_t JSONParser::GetInt64(const std::string& path)
	{
		return GetNode(path).asInt64();
	}

	void JSONParser::SetUInt8(const std::string& path, const uint8_t value)
	{
		GetNode(path) = value;
	}

	void JSONParser::SetUInt16(const std::string& path, const uint16_t value)
	{
		GetNode(path) = value;
	}

	void JSONParser::SetUInt32(const std::string& path, const uint32_t value)
	{
		GetNode(path) = value;
	}

	void JSONParser::SetUInt64(const std::string& path, const uint64_t value)
	{
		GetNode(path) = value;
	}

	uint8_t JSONParser::GetUInt8(const std::string& path)
	{
		return static_cast<uint8_t>(GetNode(path).asUInt());
	}

	uint16_t JSONParser::GetUInt16(const std::string& path)
	{
		return static_cast<uint16_t>(GetNode(path).asUInt());
	}

	uint32_t JSONParser::GetUInt32(const std::string& path)
	{
		return GetNode(path).asUInt();
	}

	uint64_t JSONParser::GetUInt64(const std::string& path)
	{
		return GetNode(path).asUInt64();
	}

	void JSONParser::SetBool(const std::string& path, bool value)
	{
		Json::Path jsonPath(path);
		Json::Value& node = jsonPath.make(root_);
		node = value;
	}

	void JSONParser::SetString(const std::string& path, const std::string& value)
	{
		Json::Path jsonPath(path);
		Json::Value& node = jsonPath.make(root_);
		node = value;
	}

	void JSONParser::SetFloat(const std::string& path, float value)
	{
		Json::Path jsonPath(path);
		Json::Value& node = jsonPath.make(root_);
		node = value;
	}

	void JSONParser::SetDouble(const std::string& path, double value)
	{
		Json::Path jsonPath(path);
		Json::Value& node = jsonPath.make(root_);
		node = value;
	}

	bool JSONParser::GetBool(const std::string& path)
	{
		return GetNode(path).asBool();
	}

	std::string JSONParser::GetString(const std::string& path)
	{
		return GetNode(path).asString();
	}

	float JSONParser::GetFloat(const std::string& path)
	{
		return GetNode(path).asFloat();
	}

	double JSONParser::GetDouble(const std::string& path)
	{
		return GetNode(path).asDouble();
	}

	Json::Value JSONParser::GetNode(const std::string& path)
	{
		Json::Path jsonPath(path);
		return jsonPath.resolve(root_);
	}

} // namespace zeus