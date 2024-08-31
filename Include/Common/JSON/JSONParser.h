#pragma once

#include "Commom.h"
#include "json/json.h"

namespace zeus
{

	class BATTLE_API JSONParser
	{
	public:

		JSONParser(const std::string& filename);

		~JSONParser() = default;

	public:

		bool Load();

		bool Save(const std::string& filename);

		void SetInt8(const std::string& path, const int8_t value);

		void SetInt16(const std::string& path, const int16_t value);

		void SetInt32(const std::string& path, const int32_t value);

		void SetInt64(const std::string& path, const int64_t value);

		int8_t GetInt8(const std::string& path);

		int16_t GetInt16(const std::string& path);

		int32_t GetInt32(const std::string& path);

		int64_t GetInt64(const std::string& path);

		void SetUInt8(const std::string& path, const uint8_t value);

		void SetUInt16(const std::string& path, const uint16_t value);

		void SetUInt32(const std::string& path, const uint32_t value);

		void SetUInt64(const std::string& path, const uint64_t value);

		uint8_t GetUInt8(const std::string& path);

		uint16_t GetUInt16(const std::string& path);

		uint32_t GetUInt32(const std::string& path);

		uint64_t GetUInt64(const std::string& path);

		void SetBool(const std::string& path, bool value);

		void SetString(const std::string& path, const std::string& value);

		void SetFloat(const std::string& path, float value);

		void SetDouble(const std::string& path, double value);

		bool GetBool(const std::string& path);

		std::string GetString(const std::string& path);

		float GetFloat(const std::string& path);

		double GetDouble(const std::string& path);

		template <typename T, template <typename, typename = std::allocator<T>> class Container>
		void SetArray(const std::string& path, const Container<T>& container)
		{
			Json::Path jsonPath(path);
			Json::Value& node = jsonPath.make(root_);
			node = Json::Value(Json::arrayValue);
			for (const T& item : container)
			{
				Json::Value value(item);
				node.append(value);
			}
		}

		template <typename T, template <typename, typename = std::allocator<T>> class Container>
		void AppendArray(const std::string& path, const Container<T>& container)
		{
			Json::Path jsonPath(path);
			Json::Value& node = jsonPath.make(root_);

			if (!node.isNull() && node.isArray())
			{
				for (const T& item : container)
				{
					node.append(Json::Value(item));
				}
				return;
			}
			SetArray(path, container);
		}

		template <typename Key, typename Value>
		void SetMap(const std::string& path, const std::map<Key, Value>& mapContainer)
		{
			Json::Path jsonPath(path);
			Json::Value& node = jsonPath.make(root_);
			node = Json::Value(Json::objectValue);
			for (const auto& pair : mapContainer)
			{
				Json::Value jsonValue(pair.second);
				node[Json::Value(pair.first).asString()] = jsonValue;
			}
		}

		template <typename Key, typename Value>
		void AppendMap(const std::string& path, const std::map<Key, Value>& mapContainer)
		{
			Json::Path jsonPath(path);
			Json::Value& node = jsonPath.make(root_);

			if (!node.isNull() && node.isObject())
			{
				for (const auto& pair : mapContainer)
				{
					node[Json::Value(pair.first).asString()] = Json::Value(pair.second);
				}
				return;
			}
			SetMap(path, mapContainer);
		}

	private:

		Json::Value GetNode(const std::string& path);

	private:

		Json::Value root_;

		std::string filename_;
	};

} // namespace zeus